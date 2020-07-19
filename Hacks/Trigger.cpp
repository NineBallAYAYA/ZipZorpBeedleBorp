//
// Created by root on 7/8/20.
//

#include "Trigger.h"
#include <unistd.h>
#include "iostream"
#include "boost/thread.hpp"

Trigger::Trigger(Memory *memory_) {
    memory = memory_;
}

void Trigger::shoot() {
     std::cout << std::hex << memory->ForceAttack_addr << "shoot! \n";
     int cool = 5;
     memory->write((void*) memory->ForceAttack_addr, &cool, sizeof(cool));
     usleep(200);
     cool = 4;
     memory->write((void*) memory->ForceAttack_addr, &cool, sizeof(cool));
}

void Trigger::check() {
        int crossID;
        memory->read((void*) (memory->InCrossID_addr), &crossID, sizeof(crossID));
        if(crossID == 0){
            return;
        }
        long int crossTarget;
        memory->read((void*) (memory->dwEntityList_addr + (crossID * 0x20)), &crossTarget, sizeof(crossTarget));
        int crossHealth;
        memory->read((void*) (crossTarget + 0x138), &crossHealth, sizeof(crossHealth));
        shoot();
}