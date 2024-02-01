#include "led_mode_list.h"

std::vector<LedMode> LedModeList::list_mode;

std::map<int, Color> LedModeList::modeFunction(int red_value, int green_value , int blue_value) {
      std::map<int, Color> result;
      result[1] = Color(red_value, blue_value, green_value);
      
      return result;
}

void LedModeList::prepare_list() {
    std::function<std::map<int, Color>(int, int, int)> modeFunction =[](int red, int blue, int green) {
            return LedModeList::modeFunction(red, blue, green);
    };

    LedMode mode1("test1", 1, false, modeFunction);
    LedMode mode2("test2", 2, false, modeFunction);
    LedModeList::list_mode.push_back(mode1);
    LedModeList::list_mode.push_back(mode2);
}

std::vector<LedMode> LedModeList::getModeList() {
    return LedModeList::list_mode;
}

std::optional<std::function<std::map<int, Color>(int, int, int)>> LedModeList::get_change_function_by_ID(int mode_id) {
    for (LedMode& led_mode : LedModeList::list_mode) {
        if (led_mode.getModeServerId() == mode_id) {
            return led_mode.getFunction();
        }
    }
    return std::nullopt;
}
