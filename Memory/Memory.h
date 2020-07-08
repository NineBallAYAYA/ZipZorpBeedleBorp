//
// Created by nate on 7/7/20.
//

#ifndef MULTIHACK_MEMORY_H
#define MULTIHACK_MEMORY_H
#include "../misc/typedef.h"
#include <string>
#include <iostream>
#include <sys/uio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <vector>

class Memory {
public:
    void getPid(const std::string&);
    void getClientModule();
    void RefreshAddr();
    int read(void* targetAddress, void* saveLocation, size_t size);
    int write(void* targetAddress, void* saveLocation, size_t size);
    addr_type multiLevelPointer(std::vector<addr_type> offsets, size_t size);
public:
//-----------------------------------------------//
    pid_t pid = 0;
//-----------------------------------------------//
    std::string clientName = "client_client.so";
    addr_Range clientAddr;
//-----------------------------------------------//
    addr_type force_jump_offset = 0x2a8e4d0;
    addr_type base_player_offset = 0x21e53b0;
    addr_type flags_offset = 0x13c;
//-----------------------------------------------//
    addr_type force_jump_addr;
    addr_type base_player_addr;
    addr_type flags_addr;
//-----------------------------------------------//
};

#endif MULTIHACK_MEMORY_H
