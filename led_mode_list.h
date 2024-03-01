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
    static std::map<int, Color> ania_effect(int red_value, int blue_value, int green_value, int amount_led);
    static std::vector<LedMode> list_mode;
    static LedMode ania_effect_creator();
    static std::map<int, Color> rainbow(int red_value, int green_value , int blue_value, int amount_led);
    static Color wheel(byte WheelPos);
    static LedMode rainbow_effect_creator();

public:
    static std::vector<LedMode> getModeList();
    static void prepare_list();
    static std::optional<std::function<std::map<int, Color>(int, int, int,int)>> get_change_function_by_ID(int change_mode_id);
};

#endif
