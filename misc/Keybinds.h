//
// Created by root on 7/8/20.
//

#ifndef MULTIHACK_KEYBINDS_H
#define MULTIHACK_KEYBINDS_H

#include "../Memory/Memory.h"
#include <linux/input.h>
#include "../Hacks/BunnyHop.h"
#include "../Hacks/Trigger.h"
#include "../Hacks/Esp.h"
#include <unistd.h>
#include "map"

class Keybinds {
public:
    Keybinds(BunnyHop* bunnyHop, Trigger* trigger, Esp* esp);
    void init();
//Class Pointers
private:
    BunnyHop* bunnyhop;
    Trigger* trigger;
    Esp* esp;
//KEYS
private:
    int bhopkey = KEY_SPACE;
    int triggerkey = KEY_C;
    int espkey = KEY_Y;
//FUNCTIONS
private:
    void read_input();
//VARIABLES
private:
    std::vector<int> deviceList;
    std::map<int, int> deviceFD;
    int InputDeviceID = NULL;
};


#endif //MULTIHACK_KEYBINDS_H
