#include "spiffs/spiffs_config.h"
#ifndef COLOR_H
#define COLOR_H

#include <functional>
#include <map>

class Color {
private:
    int red;
    int green;
    int blue;

public:
    Color(int r, int g, int b);
    Color() = default;

    int getRed() const;
    int getGreen() const;
    int getBlue() const;
    uint32_t toStripColor();
};

#endif