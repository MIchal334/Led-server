#ifndef led_mode_h
#define led_mode_h

#include <ArduinoJson.h>
#include <functional>
#include "Arduino.h"
#include <map>
#include "color.h"

class LedMode {
public:
  LedMode(String optionName, int modeServerId, bool setColor, const  std::function<std::map<int, uint32_t>(int, int, int,int)> function);
  std::function<std::map<int, uint32_t>(int, int, int,int)> getFunction();
  String getOptionName();
  int getModeServerId();
  bool isSetColor();
  DynamicJsonDocument toJson();
  
private:
  String optionName;
  int modeServerId;
  bool setColor;
  std::function<std::map<int, uint32_t>(int, int, int,int)> modeFunction;
};

#endif
