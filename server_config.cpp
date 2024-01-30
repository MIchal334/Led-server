#include "server_config.h"
#include "led_mode_list.h"
#include "change_mode_list.h"
#include "change_mode.h"

DynamicJsonDocument ServerConfig::getServerConfigInJson() {
    LedModeList ledModeListObj;
    std::vector<LedMode> ledModeList = ledModeListObj.getModeList();

    std::vector<ChangeMode> change_mode_list = ChangeModeList::get_change_list();

    DynamicJsonDocument json_config(512);
    JsonArray ledModesArray = json_config.createNestedArray("ledModes");
    JsonArray changeModesArray = json_config.createNestedArray("changeModes");

    for (size_t i = 0; i < ledModeList.size(); ++i) {
        ledModesArray.add(ledModeList[i].toJson()); 
    }

    for (size_t i = 0; i < change_mode_list.size(); ++i) {
        changeModesArray.add(change_mode_list[i].toJson()); 
    }

    return json_config;
}
