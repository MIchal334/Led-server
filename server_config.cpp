#include "server_config.h"
#include "led_mode_list.h"
#include "change_mode_list.h"

DynamicJsonDocument ServerConfig::getServerConfigInJson() {
    LedModeList ledModeListObj;
    std::vector<LedMode> ledModeList = ledModeListObj.getModeList();

    ChangeModeList chngeModeList;
    std::vector<ChangeMode> changeModeList = chngeModeList.getChangeList();

    DynamicJsonDocument json_config(512);
    JsonArray ledModesArray = json_config.createNestedArray("ledModes");
    JsonArray changeModesArray = json_config.createNestedArray("changeModes");

    for (size_t i = 0; i < ledModeList.size(); ++i) {
        ledModesArray.add(ledModeList[i].toJson()); 
    }

    for (size_t i = 0; i < changeModeList.size(); ++i) {
        changeModesArray.add(ledModeList[i].toJson()); 
    }

    return json_config;
}
