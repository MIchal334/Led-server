#include "change_mode_list.h"
#include "change_mode.h"
#include "led_config.h"

std::vector<ChangeMode> ChangeModeList::list_mode;

void ChangeModeList::wunsz(int red_value, int green_value , int blue_value, int amount_led) {
  for (int i = 0; i < amount_led; i++) {
    int j = amount_led - i;
    LedConfig::getStrip().setPixelColor(i, red_value, green_value, blue_value);
    LedConfig::getStrip().setPixelColor(j, red_value, green_value, blue_value);
    LedConfig::getStrip().setPixelColor(i - 7, 0, 0, 0);
    LedConfig::getStrip().setPixelColor(j + 7, 0, 0, 0);
    LedConfig::getStrip().show();
    delay (50);
  }
}

ChangeMode ChangeModeList::wunsz_mode_creator() {
    std::function<void(int, int, int, int)> changeFunction = [](int red_value, int green_value , int blue_value, int amount_led) {
        ChangeModeList::wunsz(red_value,green_value,blue_value,amount_led);
    };
    ChangeMode wunsz_mode("Wunsz", 1, changeFunction);
    return wunsz_mode;
}

void ChangeModeList::prepare_list() {
  ChangeModeList::list_mode.push_back(wunsz_mode_creator());
}

std::vector<ChangeMode> ChangeModeList::get_change_list() {
    return ChangeModeList::list_mode;
}

std::optional<std::function<void(int,int,int,int)>> ChangeModeList::get_change_function_by_ID(int change_mode_id) {
    for (ChangeMode& change_mode : ChangeModeList::list_mode) {
        if (change_mode.get_change_mode_server_id() == change_mode_id) {
            return change_mode.get_function();
        }
    }
    return std::nullopt;
}
