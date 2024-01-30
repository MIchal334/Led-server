#ifndef LED_MODE_LIST_H
#define LED_MODE_LIST_H

#include "Arduino.h"
#include "led_mode.h"
#include <vector>
#include <functional>
#include <optional>

class LedModeList {
private:
    static void modeFunction();
    static std::vector<LedMode> list_mode;

public:
    static std::vector<LedMode> getModeList();
    static void prepare_list();
    static std::optional<std::function<void()>> get_change_function_by_ID(int change_mode_id);
};

#endif
