//
// Created by nate on 7/7/20.
//

#ifndef MULTIHACK_MEMORY_H
#define MULTIHACK_MEMORY_H
#include "../misc/typedef.h"
#include <string>
#include <vector>

class Memory {
public:
    void getPid(const std::string&);
    void getClientModule();
    void RefreshAddr();
    int read(void* targetAddress, void* saveLocation, size_t size);
    int write(void* targetAddress, void* saveLocation, size_t size);
    addr_type multiLevelPointer(std::vector<addr_type> offsets, size_t size);
    addr_type multiLevelPointer(addr_type offset1, addr_type offset2, size_t size);
public:
//-----------------------------------------------//
    pid_t pid = 0;
///-----------------------------------------------//
    std::string clientName = "client_client.so";
    addr_Range clientAddr;
///-----------------------------------------------//
//BHop offsets
    addr_type force_jump_offset = 0x2a914d0;
    addr_type base_player_offset = 0x21e83b0;
    addr_type flags_offset = 0x13c;
//------------------------------------------------//
//ESP Offsets
    addr_type dwGlowObjectManager_offset = 0x2a83140;
   // addr_type m_iGlowIndex = 0x0;
    addr_type m_iTeamNum_offset = 0x12c;
    addr_type dwEntityList_offset = 0x2218808;
//------------------------------------------------//
//Trigger
    addr_type dwForceAttack_offset = 0x2a8bc04;
    addr_type dwInCrossID_offset = 0xcc;
///-----------------------------------------------//
//BHop addresses
    addr_type force_jump_addr = NULL;
    addr_type base_player_addr = NULL;
    addr_type flags_addr = NULL;
//------------------------------------------------//
//ESP addresses
    addr_type dwGlowObjectManager_addr = NULL;
    addr_type m_iTeamNum_addr = NULL;
    addr_type dwEntityList_addr = NULL;
//------------------------------------------------//
//Trigger
    addr_type dwForceAttack_addr = NULL;
    addr_type dwInCrossID_addr = NULL;
///-----------------------------------------------//
};

#endif //MULTIHACK_MEMORY_H
