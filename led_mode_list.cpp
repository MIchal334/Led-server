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


int rainbow_led_counter = 0;
int rainbow_effect_time_delay = 40; 
static unsigned long rainbow_effect_last_time = 0;

std::map<int, Color> LedModeList::rainbow(int red_value, int green_value , int blue_value, int amount_led) {
  std::map<int, Color> result;

 if ( millis() - rainbow_effect_last_time >= rainbow_effect_time_delay){
    for (int i = 0; i < amount_led; i++) {
      // result[i] = wheel((i * 1 + rainbow_led_counter)) & 255;
      // TODO: CHECK OLD VESRION
      result[i] = wheel((i * 1 + rainbow_led_counter));
    }
    if (rainbow_led_counter >= 255){
        rainbow_led_counter = 0;
    }
    rainbow_led_counter++;
 }
  rainbow_effect_last_time = millis();
  return result;
}

Color LedModeList::wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


LedMode LedModeList::ania_effect_creator(){
    std::function<std::map<int, Color>(int, int, int, int)> modeFunction =[](int red, int blue, int green, int amount_led) {
            return LedModeList::ania_effect(red, blue, green, amount_led);
    };

    LedMode ania_effect_mode("ania_effect", 1, false, modeFunction);
    return ania_effect_mode;
}

LedMode LedModeList::rainbow_effect_creator(){
      std::function<std::map<int, Color>(int, int, int, int)> modeFunction =[](int red, int blue, int green, int amount_led) {
            return LedModeList::rainbow(red, blue, green, amount_led);
    };

    LedMode rainbow_effect_mode("Tęcza", 2, false, modeFunction);
    return rainbow_effect_mode;
}


void LedModeList::prepare_list() {
    LedModeList::list_mode.push_back(ania_effect_creator());
    LedModeList::list_mode.push_back(rainbow_effect_creator());
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
