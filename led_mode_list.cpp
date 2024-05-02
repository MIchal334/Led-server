#include "led_mode_list.h"

std::vector<LedMode> LedModeList::list_mode;


int ania_effect_counter = 0;
int ania_effect_snke_length = 5;
int ania_color_level = 100;
int ania_effect_time_delay = 80; 
static unsigned long ania_effect_last_time = 0;

std::map<int, uint32_t> LedModeList::ania_effect(int red_value, int green_value , int blue_value, int amount_led) {

      std::map<int, uint32_t> result;
       if ( millis() - ania_effect_last_time >= ania_effect_time_delay) {
        for(int i=0; i<amount_led; ++i) {
          int led_number = i+ania_effect_counter;

          if (led_number >= amount_led ){
            led_number = led_number - amount_led;
          }

          if(i % (2*ania_effect_snke_length) < ania_effect_snke_length ){
            result[led_number] = LedConfig::getStrip().Color(0, ania_color_level, 0);
          }else{
            result[led_number] = LedConfig::getStrip().Color(ania_color_level, 0, 0);
          }
      }
      ania_effect_last_time = millis();
      ania_effect_counter++;
      if (ania_effect_counter > amount_led){
        ania_effect_counter = 0;
      }
    }
    return result;
}


int rainbow_led_counter = 0;
int rainbow_effect_time_delay = 40; 
static unsigned long rainbow_effect_last_time = 0;

std::map<int, uint32_t> LedModeList::rainbow(int red_value, int green_value, int blue_value, int amount_led) {
  std::map<int, uint32_t> result;
  if (millis() - rainbow_effect_last_time >= rainbow_effect_time_delay) {
    for (int i = 0; i < amount_led; i++) {
      result[i] = wheel((i + rainbow_led_counter) % 256);
    }
    rainbow_led_counter++;
    rainbow_effect_last_time = millis();
  }
  
  return result;
}

uint32_t LedModeList::wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return LedConfig::getStrip().Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return LedConfig::getStrip().Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return LedConfig::getStrip().Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


bool is_change_mode = false;
int random_counter  = 0;
int random_effect_time_delay = 15 * 1000; 
int randmo_effect_change_delay =  40;
static long random_effect_last_time = -random_effect_time_delay;
static long random_effect_change_last_time = 0;
std::map<int, uint32_t> random_result;
int r,g,b;

std::map<int, uint32_t> LedModeList::random_change(int red_value, int green_value, int blue_value, int amount_led) {


  if (millis() - random_effect_last_time >= random_effect_time_delay) {
    if (!is_change_mode){
      r=random(0,200);
      g=random(0,200);
      b=random(0,200);

    if ((r + g + b) <= 45){
      r = 20;
      g = 20;
      b = 20;
    }
    is_change_mode = true; 
  }
    if (millis() - random_effect_change_last_time >= randmo_effect_change_delay)
    {
    int* old_array = LedConfig::get_old_value();
    random_counter++;

    for (int i = 0; i < amount_led; i++) {
      random_result[i] = LedConfig::getStrip().Color(old_array[0], old_array[1], old_array[2]);
    }


    for (int i = 0; i < random_counter; i++) {
      random_result[i] = LedConfig::getStrip().Color(r, g, b);
    }
    
    for (int i = amount_led - 1; i > (amount_led - random_counter); i--) {
      random_result[i] = LedConfig::getStrip().Color(r, g, b);
    }

    random_effect_change_last_time = millis();

    if(random_counter >= (amount_led/2+1) ){
      random_effect_last_time = millis();
      random_counter = 0;
      LedConfig::set_old_values(r,g,b);
      is_change_mode = false;
    }

    }

  }
  
  return random_result;
}



int smooth_effect_counter = 0;
int smooth_color_level_max = 150;
int smooth_effect_time_delay = 500; 
int current_red_level = smooth_color_level_max;
int current_gren_level = 0;
int current_blue_level = 0;
static unsigned long smooth_effect_last_time = 0;



std::map<int, uint32_t> LedModeList::smooth_effect(int red_value, int green_value , int blue_value, int amount_led) {

      std::map<int, uint32_t> result;
      if ( millis() - smooth_effect_last_time >= smooth_effect_time_delay) {
        if(smooth_effect_counter % 3 == 0){
          current_gren_level++;
          current_red_level--;
          current_blue_level = 0;
          if(current_gren_level ==  smooth_color_level_max){
            smooth_effect_counter++;
          }

        }

        if(smooth_effect_counter % 3 == 1){
          current_gren_level--;
          current_red_level = 0;
          current_blue_level++;

          if(current_blue_level ==  smooth_color_level_max){
            smooth_effect_counter++;
          }

        }

        if(smooth_effect_counter % 3 == 2){
          current_gren_level = 0;
          current_red_level ++;
          current_blue_level--;

          if(current_red_level ==  smooth_color_level_max){
            smooth_effect_counter++;
          }

        }

        for(int i=0; i<amount_led; ++i) {
            result[i] = LedConfig::getStrip().Color(current_red_level, current_gren_level, current_blue_level);
        }
        smooth_effect_last_time =  millis();

    }
    return result;
}




LedMode LedModeList::ania_effect_creator(){
    std::function<std::map<int, uint32_t>(int, int, int, int)> modeFunction =[](int red, int blue, int green, int amount_led) {
            return LedModeList::ania_effect(red, blue, green, amount_led);
    };

    LedMode ania_effect_mode("Ania effect", 1, false, modeFunction);
    return ania_effect_mode;
}

LedMode LedModeList::rainbow_effect_creator(){
      std::function<std::map<int, uint32_t>(int, int, int, int)> modeFunction =[](int red, int blue, int green, int amount_led) {
            return LedModeList::rainbow(red, blue, green, amount_led);
    };

    LedMode rainbow_effect_mode("Tęcza", 2, false, modeFunction);
    return rainbow_effect_mode;
}


LedMode LedModeList::random_effect_creator(){
      std::function<std::map<int, uint32_t>(int, int, int, int)> modeFunction =[](int red, int blue, int green, int amount_led) {
            return LedModeList::random_change(red, blue, green, amount_led);
    };

    LedMode random_effect_mode("Losowy", 3, false, modeFunction);
    return random_effect_mode;
}

LedMode LedModeList::smooth_effect_creator(){
      std::function<std::map<int, uint32_t>(int, int, int, int)> modeFunction =[](int red, int blue, int green, int amount_led) {
            return LedModeList::smooth_effect(red, blue, green, amount_led);
    };

    LedMode random_effect_mode("Smukly", 4, false, modeFunction);
    return random_effect_mode;
}

void LedModeList::prepare_list() {
    LedModeList::list_mode.push_back(ania_effect_creator());
    LedModeList::list_mode.push_back(rainbow_effect_creator());
    LedModeList::list_mode.push_back(random_effect_creator());
    LedModeList::list_mode.push_back(smooth_effect_creator());

}

std::vector<LedMode> LedModeList::getModeList() {
    return LedModeList::list_mode;
}

std::optional<std::function<std::map<int, uint32_t>(int, int, int, int)>> LedModeList::get_change_function_by_ID(int mode_id) {
    for (LedMode& led_mode : LedModeList::list_mode) {
        if (led_mode.getModeServerId() == mode_id) {
            return led_mode.getFunction();
        }
    }
    return std::nullopt;
}
