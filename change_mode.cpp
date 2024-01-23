#include "Arduino.h"
#include "chaneg_mode.h"
#include <ArduinoJson.h>

ChangeMode::ChangeMode(String optionName,int changeModeServerId)
{
  this->optionName = optionName;
  this->changeModeServerId = changeModeServerId;
}

String ChangeMode::getOptionName()
{
  return this->optionName;
}

int ChangeMode::getchangeModeServerId()
{
  return this->changeModeServerId;
}

DynamicJsonDocument ChangeMode::toJson(){
  DynamicJsonDocument doc(200);
  doc["optionName"] = this->optionName;
  doc["changeModeServerId"] = this->changeModeServerId;
  return doc;
}