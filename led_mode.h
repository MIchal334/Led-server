#ifndef led_mode_h
#define led_mode_h

#include <ArduinoJson.h>
#include <functional>
#include "Arduino.h"

class LedMode {
public:
  LedMode(String optionName, int modeServerId, bool setColor, const std::function<void()>& function);
  std::function<void()> getFunction();
  String getOptionName();
  int getModeServerId();
  bool isSetColor();
  DynamicJsonDocument toJson();
  
private:
  String optionName;
  int modeServerId;
  bool setColor;
  std::function<void()> modeFunction;
};

#endif
