#include "led_config.h"

Adafruit_NeoPixel LedConfig::strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int LedConfig::old_red_value = 0;
int LedConfig::old_green_value = 0;
int LedConfig::old_blue_value = 0;

Adafruit_NeoPixel& LedConfig::getStrip() {
    return LedConfig::strip;
}


void LedConfig::set_old_values(int old_red_value, int old_green_value,int old_blue_value){
  LedConfig::old_red_value = old_red_value;
  LedConfig::old_green_value = old_green_value;
  LedConfig::old_blue_value = old_blue_value;
}


int* LedConfig::get_old_value() {
    static int old_value_list[3];
    old_value_list[0] = LedConfig::old_red_value;
    old_value_list[1] = LedConfig::old_green_value;
    old_value_list[2] = LedConfig::old_blue_value;
    return old_value_list;
}

