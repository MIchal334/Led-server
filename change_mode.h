#ifndef change_mode_h
#define change_mode_h

#include <ArduinoJson.h>
#include <functional>
#include "Arduino.h"
#include <optional>

class ChangeMode {
public:
  ChangeMode(String optionName, int changeModeServerId, const std::function<void()>& function);
  std::function<void()> get_function();
  String get_option_name();
  int get_change_mode_server_id();
  DynamicJsonDocument toJson();
  
private:
  String optionName;
  int changeModeServerId;
  std::function<void()> changeFunction;
};

#endif
