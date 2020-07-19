//
// Created by root on 7/8/20.
//

#ifndef MULTIHACK_TRIGGER_H
#define MULTIHACK_TRIGGER_H
#include "../Memory/Memory.h"

class Trigger {
public:
    Trigger(Memory* memory_);
    void check();
//FUNCTIONS
private:
    void shoot();
//CLASS PTR's
private:
    Memory* memory;
public:
    int shootDelay = 1000;
};


#endif //MULTIHACK_TRIGGER_H
