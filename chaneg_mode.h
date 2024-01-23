#ifndef change_mode.h
#define change_mode.h

#include <ArduinoJson.h>
#include "Arduino.h"


class ChangeMode {
public:
  ChangeMode(String optionName,int changeModeServerId);
  String getOptionName();
  int getchangeModeServerId();
  DynamicJsonDocument toJson();
  
private:
  String optionName;
  int changeModeServerId;
};

#endif
