#include "led_mode.h"

LedMode::LedMode(String optionName, int modeServerId, bool setColor, const std::function<void()>& function)
    : optionName(optionName), modeServerId(modeServerId), setColor(setColor), modeFunction(function) {}

String LedMode::getOptionName()
{
    return this->optionName;
}

int LedMode::getModeServerId()
{
    return this->modeServerId;
}

bool LedMode::isSetColor()
{
    return this->setColor;
}

std::function<void()> LedMode::getFunction()
{
    return modeFunction;
}

DynamicJsonDocument LedMode::toJson()
{
    DynamicJsonDocument doc(200);
    doc["optionName"] = this->optionName;
    doc["modeServerId"] = this->modeServerId;
    doc["setColor"] =  this->setColor;
    return doc;
}