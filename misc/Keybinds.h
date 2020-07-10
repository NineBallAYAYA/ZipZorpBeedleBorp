//
// Created by root on 7/8/20.
//

#ifndef MULTIHACK_KEYBINDS_H
#define MULTIHACK_KEYBINDS_H

#include "../Memory/Memory.h"
#include <linux/input.h>
#include "../Hacks/BunnyHop.h"
#include <unistd.h>

class Keybinds {
public:
    Keybinds(BunnyHop* bunnyHop);
void open_keyboard();
void open_mouse();
void sendMouse();
void readMouse();
void read_input();
void start_logging();
//--------------------------//
///polling vars
int shouldHop = 0;
int bhopkey = KEY_SPACE;
BunnyHop* bunnyhop;
//--------------------------//
private:
    int fdK;
    int fdM;
    struct input_event ie;
    struct input_event ieM;
};


#endif //MULTIHACK_KEYBINDS_H
