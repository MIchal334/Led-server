#ifndef LED_MODE_LIST_H
#define LED_MODE_LIST_H

#include "Arduino.h"
#include "led_mode.h"
#include <vector>
#include <functional>
#include <optional>
#include <map>
#include "color.h"

class LedModeList {
private:
    static std::map<int, Color> modeFunction(int red_value, int blue_value, int green_value);
    static std::vector<LedMode> list_mode;

public:
    static std::vector<LedMode> getModeList();
    static void prepare_list();
    static std::optional<std::function<std::map<int, Color>(int, int, int)>> get_change_function_by_ID(int change_mode_id);
};

#endif
