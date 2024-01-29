#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "change_mode.h"
#include <functional>
#include "server_config.h"

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

  // server.on("/color", HTTP_GET, led_off);



  server.begin();

}

void loop() {
  Serial.println(WiFi.localIP());
  server.handleClient();
  currentFunction();
  // delay(1000);
}
