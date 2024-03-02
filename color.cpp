#include <cstdint>
#include "color.h"
#include "led_config.h"

Color::Color(int r, int g, int b) : red(r), green(g), blue(b) {}

int Color::getRed() const {
    return red;
}

int Color::getGreen() const {
    return green;
}

int Color::getBlue() const {
    return blue;
}


uint32_t Color::toStripColor(){
  return LedConfig::getStrip().Color(this->red, this->green, this->blue);
}