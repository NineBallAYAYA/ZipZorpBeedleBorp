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
    //std::cout << "shoot!\n";
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
        int crossTeam = memory->readEntity(memory->dwEntityList_addr + (crossID * 0x20), memory->m_iTeamNum_offset, sizeof(int));
        int myteam;
        memory->read((void*) (memory->base_player_addr + memory->m_iTeamNum_offset), &myteam, sizeof(myteam));
        //std::cout << "Myteam: " << myteam << " CrossTeam: " << crossTeam<< std::endl;
        if (myteam != crossTeam && crossTeam != 0)
        shoot();
}