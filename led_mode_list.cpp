
#include "led_mode_list.h"

void LedModeList::modeFunction() {
    Serial.println("MODE 1");
}

std::vector<LedMode> LedModeList::getModeList() {
    std::vector<LedMode> listMode;
    std::function<void()> changeFunction = std::bind(&LedModeList::modeFunction, this);
    LedMode mode1("test1", 1, true, changeFunction);
    listMode.push_back(mode1);
    return listMode;
}
