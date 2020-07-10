//
// Created by nate on 7/7/20.
//
#ifndef MULTIHACK_BUNNYHOP_H
#define MULTIHACK_BUNNYHOP_H

#include "../Memory/Memory.h"

class BunnyHop {
public:
    BunnyHop(Memory* memory);
    void check();
private:
    void jump();
    Memory* memory;
};


#endif MULTIHACK_BUNNYHOP_H
