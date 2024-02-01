#ifndef change_mode_h
#define change_mode_h

#include <ArduinoJson.h>
#include <functional>
#include "Arduino.h"
#include <optional>
#include <map>

class ChangeMode {
public:
  ChangeMode(String optionName, int changeModeServerId, const std::function<void(int, int, int,int)>& function);
  std::function<void(int, int, int,int)> get_function();
  String get_option_name();
  int get_change_mode_server_id();
  DynamicJsonDocument toJson();
  
private:
  String optionName;
  int changeModeServerId;
  std::function<void(int, int, int,int)> changeFunction;
};

#endif
