#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include "Arduino.h"
#include "led_mode.h"
#include "change_mode.h"
#include <vector>
#include "led_mode_list.h"
#include "change_mode_list.h"

class ServerConfig {
private:
    std::vector<LedMode> ledModes;
    std::vector<ChangeMode> changeModes;

public:
    DynamicJsonDocument getServerConfigInJson();
};

#endif