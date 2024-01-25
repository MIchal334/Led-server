#ifndef LED_MODE_LIST_H
#define LED_MODE_LIST_H

#include "Arduino.h"
#include "led_mode.h"
#include <vector>

class LedModeList {
private:
    void modeFunction();

public:
    std::vector<LedMode> getModeList();
};

#endif
