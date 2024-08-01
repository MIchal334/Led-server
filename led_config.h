#ifndef LED_CONFIG_H
#define LED_CONFIG_H

#include <Adafruit_NeoPixel.h>

#define PIN 14 // pin 5 na plytce
#define NUMPIXELS  150

class LedConfig {
private:
    static Adafruit_NeoPixel strip;
    static int old_red_value;
    static int old_green_value;
    static int old_blue_value;

public:
    static Adafruit_NeoPixel& getStrip();
    static void set_old_values(int old_red_value, int old_green_value, int old_blue_value);
    static int* get_old_value();
};



#endif
