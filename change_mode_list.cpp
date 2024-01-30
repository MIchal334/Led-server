#include "change_mode_list.h"
#include "change_mode.h"

std::vector<ChangeMode> ChangeModeList::list_mode;

void ChangeModeList::mode_1_Function() {
    Serial.println("MODE 1");
}

void ChangeModeList::prepare_list() {
    std::function<void()> changeFunction = []() {
        ChangeModeList::mode_1_Function();
    };

    ChangeMode mode1("test1", 1, changeFunction);
    ChangeModeList::list_mode.push_back(mode1);
}

std::vector<ChangeMode> ChangeModeList::get_change_list() {
    Serial.println(ChangeModeList::list_mode.size());
    return ChangeModeList::list_mode;
}

std::optional<std::function<void()>> ChangeModeList::get_change_function_by_ID(int change_mode_id) {
    for (ChangeMode& change_mode : ChangeModeList::list_mode) {
        if (change_mode.get_change_mode_server_id() == change_mode_id) {
            return change_mode.get_function();
        }
    }
    return std::nullopt;
}
