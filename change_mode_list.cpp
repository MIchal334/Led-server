#include <cstdint>
#include "change_mode_list.h"
#include "change_mode.h"
#include "led_config.h"

std::vector<ChangeMode> ChangeModeList::list_mode;


int wunsz_counter = 0;
int wunsz_delay = 50;
static unsigned long wunsz_effect_last_time = 0;
std::map<int, uint32_t> result_wunsz;

std::map<int, uint32_t> ChangeModeList::wunsz(int red_value, int green_value , int blue_value, int amount_led) {

  if (wunsz_counter > amount_led){
    std::map<int, uint32_t> result;
    wunsz_counter = 0;
    return result;
  }
  if (millis() - wunsz_effect_last_time >= wunsz_delay){
  int j = amount_led - wunsz_counter;
  result_wunsz[wunsz_counter] = LedConfig::getStrip().Color(red_value,green_value, blue_value);
  result_wunsz[j] = LedConfig::getStrip().Color(red_value,green_value, blue_value);
  result_wunsz[wunsz_counter - 7] = LedConfig::getStrip().Color(0,0,0);
  result_wunsz[j+7] = LedConfig::getStrip().Color(0,0,0);
  wunsz_counter++;
  wunsz_effect_last_time = millis();
  }

  return result_wunsz;
}


std::map<int, uint32_t> result_protektor;
int proketkor_delay = 150;
static unsigned long protektor_effect_last_time = 0;
int prot_counter = 0;
int amount_prot = 20;

std::map<int, uint32_t> ChangeModeList::protektor(int red_value, int green_value , int blue_value, int amount_led) {
  if (prot_counter > amount_prot){
    std::map<int, uint32_t> result;
    prot_counter = 0;
    return result;
  }

  if (millis() - protektor_effect_last_time >= proketkor_delay){
    uint32_t color =  Color::randomColor();
    for (int i = 0; i < amount_led; i++) {
      result_protektor[i] = color;
    }
    protektor_effect_last_time = millis();
    prot_counter++;
  }

  if (millis() - protektor_effect_last_time >= 2*proketkor_delay/3){
    for (int i = 0; i < amount_led; i++) {
      result_protektor[i] = LedConfig::getStrip().Color(0,0,0);
    }
  }

  return result_protektor;
}


std::map<int, uint32_t> result_soft;
int soft_delay = 70;
static unsigned long soft_effect_last_time = 0;
int soft_current_red = 0;
int soft_current_green = 0;
int soft_current_blue = 0;
bool soft_flag = false;

std::map<int, uint32_t> ChangeModeList::soft(int red_value, int green_value , int blue_value, int amount_led) {
  if (!soft_flag){
    int* old_array  = LedConfig::get_old_value();
    soft_current_red = old_array[0];
    soft_current_green = old_array[1];
    soft_current_blue = old_array[2];
    soft_flag = true;
  }

  if (soft_current_red == red_value && soft_current_green == green_value && soft_current_blue == blue_value ){
    std::map<int, uint32_t> result;
    soft_flag = false;
    return result;
  }


  if (millis() - soft_effect_last_time >= soft_delay){
    if (soft_current_red > red_value){
      soft_current_red--;
    }else if(soft_current_red < red_value){
      soft_current_red++;
    }

    if (soft_current_green > green_value){
      soft_current_green--;
    }else if(soft_current_green < green_value){
      soft_current_green++;
    }

    if (soft_current_blue > blue_value){
      soft_current_blue--;
    }else if(soft_current_blue < blue_value){
      soft_current_blue++;
    }


    uint32_t color = LedConfig::getStrip().Color(soft_current_red,soft_current_green,soft_current_blue);
    for (int i = 0; i < amount_led; i++) {
      result_soft[i] = color;
    }
    soft_effect_last_time = millis();
  }
  return result_soft;
}


ChangeMode ChangeModeList::wunsz_mode_creator() {
    std::function<std::map<int, uint32_t>(int, int, int, int)> changeFunction = [](int red_value, int green_value , int blue_value, int amount_led) {
        return ChangeModeList::wunsz(red_value,green_value,blue_value,amount_led);
    };
    ChangeMode wunsz_mode("Wunsz", 1, changeFunction);
    return wunsz_mode;
}



ChangeMode ChangeModeList::prot_mode_creator() {
    std::function<std::map<int, uint32_t>(int, int, int, int)> changeFunction = [](int red_value, int green_value , int blue_value, int amount_led) {
        return ChangeModeList::protektor(red_value,green_value,blue_value,amount_led);
    };
    ChangeMode protektor_mode("Prot", 2, changeFunction);
    return protektor_mode;
}



ChangeMode ChangeModeList::soft_mode_creator() {
    std::function<std::map<int, uint32_t>(int, int, int, int)> changeFunction = [](int red_value, int green_value , int blue_value, int amount_led) {
        return ChangeModeList::soft(red_value,green_value,blue_value,amount_led);
    };
    ChangeMode soft_mode("Soft", 3, changeFunction);
    return soft_mode;
}

void ChangeModeList::prepare_list() {
  ChangeModeList::list_mode.push_back(wunsz_mode_creator());
  ChangeModeList::list_mode.push_back(prot_mode_creator());
  ChangeModeList::list_mode.push_back(soft_mode_creator());
}

std::vector<ChangeMode> ChangeModeList::get_change_list() {
    return ChangeModeList::list_mode;
}

std::optional<std::function<std::map<int, uint32_t>(int,int,int,int)>> ChangeModeList::get_change_function_by_ID(int change_mode_id) {
    for (ChangeMode& change_mode : ChangeModeList::list_mode) {
        if (change_mode.get_change_mode_server_id() == change_mode_id) {
            return change_mode.get_function();
        }
    }
    return std::nullopt;
}
