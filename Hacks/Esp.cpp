//
// Created by root on 7/8/20.
//

#include "Esp.h"
#include "iostream"
#include <unistd.h>


Esp::Esp(Memory *memory_) {
    memory = memory_;
}
void Esp::init() {
    ESP = boost::thread(&Esp::cycleEntitys, this);
}

void Esp::cycleEntitys() {
    while (true) {
        usleep(1000);
        if (espOn) {
            for (int i = 0; i < 64; i++) {
                addr_type player;
                addr_type index = 0x40 * i;
                memory->read((void *) (memory->dwGlowObjectManager_addr + index), &player, sizeof(player));

                int health;
                memory->read((void *) (player + memory->m_iHealth_offset), &health, sizeof(health));
                //To rough check if its a player
                if (health > 0 && health < 101) {
                    int team;
                    int myteam;
                    memory->read((void *) (memory->base_player_addr + memory->m_iTeamNum_offset), &myteam, sizeof(myteam));
                    memory->read((void *) (player + memory->m_iTeamNum_offset), &team, sizeof(team));
                    //finer check on if its a player as well as retriving info
                    if (team != myteam) {
                        float r = (100.0 - health) / 100;
                        float g = health / 100.0;
                        setColour(index, r, g, 0, 1.0, true, false);
                    } else if (team == myteam) {
                        setColour(index, 0, 0, 1.0, 1.0, true, false);
                    }
                }

            }
        }
    }
}

void Esp::setColour(int index, float r, float g, float b, float a, bool Occluded, bool UnOccluded) {
    memory->write((void *) (memory->dwGlowObjectManager_addr + index + 0x08), &r, sizeof(r));//R
    memory->write((void *) (memory->dwGlowObjectManager_addr + index + 0x0C), &g, sizeof(g));//G
    memory->write((void *) (memory->dwGlowObjectManager_addr + index + 0x10), &b, sizeof(b));//B
    memory->write((void *) (memory->dwGlowObjectManager_addr + index + 0x14), &a, sizeof(a));//A
    memory->write((void *) (memory->dwGlowObjectManager_addr + index + 0x28), &Occluded, sizeof(Occluded));//Occluded
    memory->write((void *) (memory->dwGlowObjectManager_addr + index + 0x29), &UnOccluded,
                  sizeof(UnOccluded));//UnOccluded
}

