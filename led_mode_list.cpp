#include "led_mode_list.h"
#include "led_mode.h"

std::vector<LedMode> LedModeList::list_mode;

void LedModeList::modeFunction() {
    Serial.println("MODE 1");
}

void LedModeList::prepare_list() {
    std::function<void()> changeFunction = []() {
        LedModeList::modeFunction();
    };
    LedMode mode1("test1", 1, true, changeFunction);
    LedMode mode2("test2", 1, true, changeFunction);
    LedModeList::list_mode.push_back(mode1);
    LedModeList::list_mode.push_back(mode2);
}

std::vector<LedMode> LedModeList::getModeList() {
    return LedModeList::list_mode;
}

std::optional<std::function<void()>> LedModeList::get_change_function_by_ID(int mode_id) {
    for (LedMode& led_mode : LedModeList::list_mode) {
        if (led_mode.getModeServerId() == mode_id) {
            return led_mode.getFunction();
        }
    }
    return std::nullopt;
}
