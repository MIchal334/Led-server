#include "change_mode_list.h"

void ChangeModeList::mode1Function() {
    Serial.println("MODE 1");
}

std::vector<ChangeMode> ChangeModeList::getChangeList() {
    std::vector<ChangeMode> listMode;
    std::function<void()> changeFunction = std::bind(&ChangeModeList::mode1Function, *this);
    ChangeMode mode1("test1", 1, changeFunction);
    listMode.push_back(mode1);
    return listMode;
}
