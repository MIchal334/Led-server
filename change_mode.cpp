#include "change_mode.h"

ChangeMode::ChangeMode(String optionName, int changeModeServerId, const std::function<void(int,int,int,int)>& function)
    : optionName(optionName), changeModeServerId(changeModeServerId), changeFunction(function) {}

String ChangeMode::get_option_name()
{
    return this->optionName;
}

int ChangeMode::get_change_mode_server_id()
{
    return this->changeModeServerId;
}

std::function<void(int,int,int,int)> ChangeMode::get_function()
{
  return this->changeFunction;
}

DynamicJsonDocument ChangeMode::toJson()
{
    DynamicJsonDocument doc(200);
    doc["optionName"] = this->optionName;
    doc["changeModeServerId"] = this->changeModeServerId;
    return doc;
}
