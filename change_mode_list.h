// change_mode_list.h
#ifndef CHANGE_MODE_LIST_H
#define CHANGE_MODE_LIST_H

#include "Arduino.h"
#include "change_mode.h"
#include <vector>
#include <functional>

class ChangeModeList {
private:
    void mode1Function();

public:
    std::vector<ChangeMode> getChangeList();
};

#endif
