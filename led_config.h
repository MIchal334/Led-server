// led_config.h
#ifndef LED_CONFIG_H
#define LED_CONFIG_H

#include <Adafruit_NeoPixel.h>

#define PIN           6  
#define NUMPIXELS     100  

class LedConfig {
private:
    static Adafruit_NeoPixel* strip;

public:
    static Adafruit_NeoPixel& getStrip();
};

#endif
