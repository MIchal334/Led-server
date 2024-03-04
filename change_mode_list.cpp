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

// void ChangeModeList::protektor(int red_value, int green_value , int blue_value, int amount_led) {
//   for ( int j = 0; j < 15; j++) {
//     uint32_t color =  Color::randomColor();
//     LedConfig::getStrip().clear();
//     LedConfig::getStrip().show();
//     delay (50);
//     for (int i = 0; i < amount_led; i++) {
//       LedConfig::getStrip().setPixelColor(i, color);
//     }
//     LedConfig::getStrip().show();
//     delay(100);
//   }
// }



ChangeMode ChangeModeList::wunsz_mode_creator() {
    std::function<std::map<int, uint32_t>(int, int, int, int)> changeFunction = [](int red_value, int green_value , int blue_value, int amount_led) {
        return ChangeModeList::wunsz(red_value,green_value,blue_value,amount_led);
    };
    ChangeMode wunsz_mode("Wunsz", 1, changeFunction);
    return wunsz_mode;
}



// ChangeMode ChangeModeList::prot_mode_creator() {
//     std::function<void(int, int, int, int)> changeFunction = [](int red_value, int green_value , int blue_value, int amount_led) {
//         ChangeModeList::protektor(red_value,green_value,blue_value,amount_led);
//     };
//     ChangeMode protektor_mode("Prot", 2, changeFunction);
//     return protektor_mode;
// }

void ChangeModeList::prepare_list() {
  ChangeModeList::list_mode.push_back(wunsz_mode_creator());
  // ChangeModeList::list_mode.push_back(prot_mode_creator());
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
