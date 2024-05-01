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
#include <Adafruit_NeoPixel.h>
#include "color.h"
#include "led_config.h"

// const char *ssid = "TP-Link_D2C2";
// const char *password = "08275929";


const char *ssid = "NETIASPOT-2.4GHz-u5sK";
const char *password = "x4vt62TT";
  

// const char *ssid = "tzg_dom_1";
// const char *password = "438865980";
Adafruit_NeoPixel strip;

ESP8266WebServer server(8080);
IPAddress ip(192, 168, 0, 177);

int current_red_value = 0;
int current_blue_value = 0;
int current_green_value = 0;
int current_change_mode_id = 0;


std::map<int, uint32_t> empty(int a, int b, int c, int d){
  std::map<int, uint32_t> result;
  return result;
}

std::function<std::map<int, uint32_t>(int, int, int, int)> currentFunction = empty;
std::function<std::map<int, uint32_t>(int,int,int,int)> current_change_mode_function = empty;

bool run_new_color;
bool is_started;
bool run_change_mode;

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
  currentFunction = empty;
  for(int i=0; i<strip.numPixels(); ++i){
       strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show(); 
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
      server.send(201, "text/html");
      return ClientRequest(red_value,blue_value, green_value,change_mode_id);
    }
  } else {
    server.send(400, "text/html", "Missing JSON data");
  }
  return std::nullopt;
}


void handle_new_color_endpoint(){
  std::optional<ClientRequest> clientRequestOptional = get_object_from_json();
  if (clientRequestOptional.has_value()) {
      int* old_vlaue = LedConfig::get_old_value();
      LedConfig::set_old_values(old_vlaue[0],old_vlaue[1],old_vlaue[2]);
      ClientRequest clientRequest = clientRequestOptional.value();
      currentFunction = empty;
      current_red_value = clientRequest.get_red_value();
      current_blue_value = clientRequest.get_blue_value();
      current_green_value = clientRequest.get_green_value();
      std::optional<std::function<std::map<int, uint32_t>(int, int, int, int)>> change_function_optional = ChangeModeList::get_change_function_by_ID(clientRequest.get_change_mode_id());
      if (change_function_optional.has_value()) {
        current_change_mode_function = change_function_optional.value();
      }
      run_change_mode = true;
      strip.clear();
    }
    clientRequestOptional = std::nullopt; 
}


void set_color(int red, int green, int blue){
    for(int i=0; i<strip.numPixels(); ++i){
       strip.setPixelColor(i, strip.Color(red, green,blue));
    }
    strip.show(); 
}


void run_led_mode(){
  current_change_mode_id = 0;
  run_new_color = false;
  std::optional<ClientRequest> clientRequestOptional = get_object_from_json();
  if (clientRequestOptional.has_value()) {
      run_new_color = false;
      current_change_mode_function = empty;
      ClientRequest clientRequest = clientRequestOptional.value();
      std::optional<std::function<std::map<int, uint32_t>(int, int, int, int)>> change_function_optional= LedModeList::get_change_function_by_ID(clientRequest.get_change_mode_id());
      if (change_function_optional.has_value()) {
        currentFunction = change_function_optional.value();
        current_red_value = clientRequest.get_red_value();
        current_blue_value = clientRequest.get_blue_value();
        current_green_value = clientRequest.get_green_value();
      }
    LedConfig::set_old_values(current_red_value,current_green_value,current_blue_value);
    clientRequestOptional = std::nullopt; 
    } 
}

void turn_on_led_mode_color(std::map<int, uint32_t> led_result_map){
    for (const auto& pair : led_result_map) {
      strip.setPixelColor(pair.first, pair.second);
    }
    strip.show();
}


void start(){
  int r = random(10, 200);
  int g = random(10, 200);
  int b = random(10, 200);
  uint32 color = LedConfig::getStrip().Color(r, g, b);
  LedConfig::set_old_values(r,g,b);

  for(int i=0; i<strip.numPixels(); ++i){
       strip.setPixelColor(i, color);
  }
  strip.show(); 
}

void setup() {
  run_new_color = false;
  run_change_mode = false;
  Serial.begin(115200);
  pinMode(PIN, OUTPUT);


  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }


  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/config", HTTP_GET, handle_config);
  server.on("/test", HTTP_GET, handle_test);
  server.on("/off", HTTP_PUT, led_off);
  server.on("/color", HTTP_POST, handle_new_color_endpoint);
  server.on("/mode", HTTP_POST, run_led_mode);
  server.begin();

  ChangeModeList::prepare_list();
  LedModeList::prepare_list();
  Serial.println("Watiing for strip");
  strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); 
  strip.begin();
  delay(400);
  is_started = false;
  randomSeed(analogRead(0));
  
}

void loop() {
  server.handleClient();
  if (!is_started){
     start();
     is_started = true;
  }
  std::map<int, uint32_t> led_result_map = currentFunction(current_red_value,current_blue_value,current_green_value,strip.numPixels());
  if(led_result_map.size() > 0 ){
      turn_on_led_mode_color(led_result_map);
  }

  if (run_change_mode){
  std::map<int, uint32_t> change_result_map = current_change_mode_function(current_red_value,current_green_value,current_blue_value,strip.numPixels());
    if (change_result_map.size() <= 0){
      run_change_mode = false;
      run_new_color = true; 
    }
  turn_on_led_mode_color(change_result_map);
  }

  if (run_new_color){
    set_color(current_red_value, current_green_value, current_blue_value);
    run_new_color = false;
  }
}
