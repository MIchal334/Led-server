#include "led_config.h"

Adafruit_NeoPixel LedConfig::strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel& LedConfig::getStrip() {
    return LedConfig::strip;
}
