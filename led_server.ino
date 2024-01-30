#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "change_mode.h"
#include <functional>
#include "server_config.h"
#include "client_request.h"
#include <optional>
#include "change_mode_list.h"
#include "change_mode.h"

// const char *ssid = "TP-Link_D2C2";
// const char *password = "08275929";

const char *ssid = "tzg_dom_1";
const char *password = "438865980";

ESP8266WebServer server(8080);
IPAddress ip(192, 168, 0, 177); 


void empty(){
}

std::function<void()> currentFunction = empty ;



void handle_config() {
  ServerConfig server_config;
  DynamicJsonDocument server_config_json  = server_config.getServerConfigInJson();

  String response;
  serializeJsonPretty(server_config_json, response);

  server.send(200, "application/json", response);
}


void handle_test() {
  server.send(200, "application/json");
}



void led_off() {
  Serial.println("LED_OFF");
  server.send(204, "application/json");
}



std::optional<ClientRequest> get_object_from_json() {
  if (server.hasArg("plain")) {
    String jsonString = server.arg("plain");
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, jsonString);
    if (error) {
      server.send(400, "text/html", "Error parsing JSON");
    } else {
      
      int red_value = doc["redValue"].as<int>();
      int blue_value = doc["blueValue"].as<int>();
      int green_value = doc["greenValue"].as<int>();
      int change_mode_id = doc["changeServerId"].as<int>();

      Serial.println("NEW COLOR REQUEST");
      Serial.println(blue_value);
      server.send(201, "text/html");
      return ClientRequest(red_value,blue_value, green_value,change_mode_id);
    }
  } else {
    server.send(400, "text/html", "Missing JSON data");
  }
  return std::nullopt;
}


void set_new_color(){
  std::optional<ClientRequest> clientRequestOptional = get_object_from_json();
  if (clientRequestOptional.has_value()) {
      ClientRequest clientRequest = clientRequestOptional.value();
      run_change_mode(clientRequest.get_change_mode_id());
      set_color(clientRequest.get_red_value(),clientRequest.get_green_value(),clientRequest.get_blue_value());
    } 
}



void run_change_mode(int change_mode_id){
  
  std::optional<std::function<void()>> change_function_optional = ChangeModeList::get_change_function_by_ID(change_mode_id);
  
  if (change_function_optional.has_value()) {
    Serial.println("Changes found");
    std::function<void()> change_function = change_function_optional.value();
    change_function();
  }

}

void set_color(int red, int green, int blue){
    Serial.println("SET COLOR");
}


void setup() {
  Serial.begin(115200);


  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }


  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/config", HTTP_GET, handle_config);
  server.on("/test", HTTP_GET, handle_test);
  server.on("/off", HTTP_PUT, led_off);
  server.on("/color", HTTP_POST, set_new_color);
  server.begin();

  ChangeModeList::prepare_list();
  LedModeList::prepare_list();

}

void loop() {
  // Serial.println(WiFi.localIP());
  server.handleClient();
  currentFunction();
  // delay(1000);
}
