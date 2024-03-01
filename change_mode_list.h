#ifndef CHANGE_MODE_LIST_H
#define CHANGE_MODE_LIST_H

#include "Arduino.h"
#include "change_mode.h"
#include <vector>
#include <functional>
#include <optional>

class ChangeModeList {
private:
    static std::vector<ChangeMode> list_mode;
    static void wunsz(int red_value, int green_value , int blue_value, int amount_led);
    static ChangeMode wunsz_mode_creator();

public:
    static std::vector<ChangeMode> get_change_list();
    static std::optional<std::function<void(int, int, int,int)>> get_change_function_by_ID(int change_mode_id);
    static void prepare_list();
};

#endif
