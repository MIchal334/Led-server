#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "change_mode.h"
#include <functional>
#include "change_mode_list.h"

const char *ssid = "TP-Link_D2C2";
const char *password = "08275929";
ESP8266WebServer server(8080);
IPAddress ip(192, 168, 0, 177); 


void empty(){
}

std::function<void()> currentFunction = empty ;



void handleConfig() {
  ChangeModeList changeModeListObj;
  std::vector<ChangeMode> changeModeList  = changeModeListObj.getChangeList();
  DynamicJsonDocument json_mode = changeModeList[0].toJson();

  String response;
  serializeJsonPretty(json_mode, response);

  server.send(200, "application/json", response);
  currentFunction = changeModeList[0].getFunction();
}


// void handleTest() {
  
// if (true) {

//     String jsonString = server.arg(0);

//     Serial.println(jsonString);
//     StaticJsonDocument<200> doc;
//     DeserializationError error = deserializeJson(doc, jsonString);

//     if (error) {
//       server.send(400, "text/html", "Error parsing JSON");
//     } else {
      
//       std::vector<String> list; 

//       String name = doc["name"].as<String>();
      
//       JsonArray listArray = doc["list"].as<JsonArray>();
//       for (JsonVariant value : listArray) {
//         list.push_back(value.as<String>());
//       }

//       Test testObject(name,list);

//       String response = "Name: " + testObject.getName() + ", List: ";
//       for (const auto &item : testObject.getList()) {
//         response += item + " ";
//       }

//       server.send(200, "text/html", response);
//     }
//   } else {
//     server.send(400, "text/html", "Missing JSON data");
//   }
// }



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
  server.begin();

}

void loop() {
  // Serial.println(WiFi.localIP());
  server.handleClient();
  currentFunction();
  delay(1000);
}
