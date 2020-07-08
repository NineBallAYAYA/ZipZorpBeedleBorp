//
// Created by nate on 7/7/20.
//

#include "BunnyHop.h"
#include <unistd.h>

BunnyHop::BunnyHop(Memory* memoryptr) {
    memory = memoryptr;
}

void BunnyHop::jump() {
    unsigned int jump = 5;

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
