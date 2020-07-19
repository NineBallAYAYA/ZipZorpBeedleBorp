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

//FUNCTIONS
private:
    void jump();

//CLASS PTR's
private:
    Memory* memory;

//User Vars
public:
    int bhopDelay = 1000;
};


#endif MULTIHACK_BUNNYHOP_H
