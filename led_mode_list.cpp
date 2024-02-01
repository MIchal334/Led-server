#include "led_mode_list.h"

std::vector<LedMode> LedModeList::list_mode;


int ania_effect_counter = 0;
int ania_effect_snke_length = 5;
int ania_color_level = 100;
int ania_effect_time_delay = 1000; 
static unsigned long ania_effect_last_time = 0;

std::map<int, Color> LedModeList::ania_effect(int red_value, int green_value , int blue_value, int amount_led) {
      std::map<int, Color> result;
       if ( millis() - ania_effect_last_time >= ania_effect_time_delay) {
        for(int i=0; i<amount_led; ++i) {
          int led_number = i+ania_effect_counter;

          if (led_number >= amount_led ){
            led_number = led_number - amount_led;
          }

          if(i % (2*ania_effect_snke_length) < ania_effect_snke_length ){
            result[led_number] = Color(0, 0, ania_color_level);
          }else{
            result[led_number] = Color(ania_color_level, 0, 0);
          }
      }
      ania_effect_last_time = millis();
      ania_effect_counter++;
    }
    return result;
}



void LedModeList::prepare_list() {
    std::function<std::map<int, Color>(int, int, int, int)> modeFunction =[](int red, int blue, int green, int amount_led) {
            return LedModeList::ania_effect(red, blue, green, amount_led);
    };

    LedMode mode1("test1", 1, false, modeFunction);
    LedMode mode2("test2", 2, false, modeFunction);
    LedModeList::list_mode.push_back(mode1);
    LedModeList::list_mode.push_back(mode2);
}

std::vector<LedMode> LedModeList::getModeList() {
    return LedModeList::list_mode;
}

std::optional<std::function<std::map<int, Color>(int, int, int, int)>> LedModeList::get_change_function_by_ID(int mode_id) {
    for (LedMode& led_mode : LedModeList::list_mode) {
        if (led_mode.getModeServerId() == mode_id) {
            return led_mode.getFunction();
        }
    }
    return std::nullopt;
}
