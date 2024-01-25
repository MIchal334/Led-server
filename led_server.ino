#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "change_mode.h"
#include <functional>
#include "server_config.h"

const char *ssid = "TP-Link_D2C2";
const char *password = "08275929";
ESP8266WebServer server(8080);
IPAddress ip(192, 168, 0, 177); 


void empty(){
}

std::function<void()> currentFunction = empty ;



void handleConfig() {
  ServerConfig server_config;
  DynamicJsonDocument server_config_json  = server_config.getServerConfigInJson();

  String response;
  serializeJsonPretty(server_config_json, response);

  server.send(200, "application/json", response);
}


void handleTest() {
  server.send(200, "application/json");
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


  // server.on("/test", HTTP_POST, handleTest);

  server.on("/config", HTTP_GET, handleConfig);
  server.on("/test", HTTP_GET, handleTest);


  server.begin();

}

void loop() {
  // Serial.println(WiFi.localIP());
  server.handleClient();
  currentFunction();
  delay(1000);
}
