//
// Created by nate on 7/7/20.
//

#include "BunnyHop.h"
#include <unistd.h>
#include "iostream"

BunnyHop::BunnyHop(Memory* memoryptr) {
    memory = memoryptr;
}

int debug = 1;

void BunnyHop::jump() {
    int jump = 5;
    memory->write((void*) (memory->force_jump_addr), &jump, sizeof(int));
    usleep(2000);
    jump = 4;
    memory->write((void*) (memory->force_jump_addr), &jump, sizeof(int));
}


void BunnyHop::check() {
    int flags = 0;
    memory->read((void*) (memory->flags_addr), &flags, sizeof(int));
    if (flags == 257){
        jump();
    }
}
