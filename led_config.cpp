#include "led_config.h"

Adafruit_NeoPixel* LedConfig::strip = nullptr;

Adafruit_NeoPixel& LedConfig::getStrip() {
    if (LedConfig::strip == nullptr) {
        LedConfig::strip = new Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
    }
    return *LedConfig::strip;
}
