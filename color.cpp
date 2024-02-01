#include "color.h"


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
