#ifndef change_mode_h
#define change_mode_h

#include <ArduinoJson.h>
#include <functional>
#include "Arduino.h"

class ChangeMode {
public:
  ChangeMode(String optionName, int changeModeServerId, const std::function<void()>& function);
  std::function<void()> getFunction();
  String getOptionName();
  int getChangeModeServerId();
  DynamicJsonDocument toJson();
  
private:
  String optionName;
  int changeModeServerId;
  std::function<void()> changeFunction;
};

#endif
