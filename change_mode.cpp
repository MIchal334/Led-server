#include "change_mode.h"

ChangeMode::ChangeMode(String optionName, int changeModeServerId, const std::function<void()>& function)
    : optionName(optionName), changeModeServerId(changeModeServerId), changeFunction(function) {}

String ChangeMode::getOptionName()
{
    return this->optionName;
}

int ChangeMode::getChangeModeServerId()
{
    return this->changeModeServerId;
}

std::function<void()> ChangeMode::getFunction()
{
  return changeFunction;
}

DynamicJsonDocument ChangeMode::toJson()
{
    DynamicJsonDocument doc(200);
    doc["optionName"] = this->optionName;
    doc["changeModeServerId"] = this->changeModeServerId;
    return doc;
}
