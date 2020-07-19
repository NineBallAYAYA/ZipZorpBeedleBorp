//
// Created by nate on 7/7/20.
//

#include "Memory.h"
#include "../misc/Misc.h"
#include <regex>
#include <iostream>
#include <sys/uio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <sys/uio.h>
#include <stdlib.h>

//Fairly straightforward
void Memory::getPid(const std::string& procName) {
    std::string cmd = "pidof -s " + procName;
    std::string pidStr = GetStdoutFromCommand(cmd);
    if (pidStr == "") return;
    pid = std::stoul(pidStr);
}

void Memory::getClientModule() {
    //----------------------------------------------------//
    //Get Module Addr
    std::string cmd = "grep " + clientName + " /proc/" + std::to_string(pid) + "/maps | head -n 1";
    std::string clientAddrUnformated = GetStdoutFromCommand(cmd);

    //----------------------------------------------------//
    //Regex to test and isolate starting addr
    std::smatch sm; std::regex e ("^(.+?)-(.+?)\\s");
    std::regex_match (clientAddrUnformated,sm,e);

    //----------------------------------------------------//
    //Logging...
    if(sm.size() == 0){
        std::cout << "Failed to load Client module" << std::endl;
    }
    std::string start = sm[1];
    std::string end = sm[2];

    clientAddr = addr_Range(strtoul(start.c_str(), NULL, 16), strtoul(end.c_str(), NULL, 16));
    std::cout << clientAddrUnformated << std::endl;
    std::cout << "Found Client Module: " << start << std::endl;
}

int Memory::read(void* remoteAddr, void* localAddr, size_t size) {
    struct iovec local_mem;
    struct iovec remote_mem;
    local_mem.iov_base = localAddr;
    local_mem.iov_len = size;
    remote_mem.iov_base = remoteAddr;
    remote_mem.iov_len = size;
    return process_vm_readv(pid, &local_mem, 1, &remote_mem, 1, 0);
}

int Memory::write(void* remoteAddr, void* localAddr, size_t size) {
    struct iovec local_mem;
    struct iovec remote_mem;
    local_mem.iov_base = localAddr;
    local_mem.iov_len = size;
    remote_mem.iov_base = remoteAddr;
    remote_mem.iov_len = size;
    return process_vm_writev(pid, &local_mem, 1, &remote_mem, 1, 0);
}

void Memory::RefreshAddr() {
//------------------------------------------------//
    read((void*) (clientAddr.first + base_player_offset), &base_player_addr, sizeof(base_player_addr));
    force_jump_addr  =  clientAddr.first  +  force_jump_offset;
    ForceAttack_addr = clientAddr.first + ForceAttack_offset;
    InCrossID_addr = base_player_addr + InCrossID_offset;
    std::cout << "CrossID: " << InCrossID_addr << std::endl;
//------------------------------------------------//
    flags_addr = base_player_addr + flags_offset;

//------------------------------------------------//
    dwGlowObjectManager_addr = clientAddr.first + dwGlowObjectManager_offset;
    dwEntityList_addr = clientAddr.first + dwEntityList_offset;
//------------------------------------------------//
}

addr_type Memory::multiLevelPointer(std::vector<addr_type> offsets, size_t size) {
    addr_type NextOffset = 0;
    addr_type CurrentOffset = 0;
    for (int i = 0; i < offsets.size(); i++){
        CurrentOffset = offsets[i] + NextOffset;
        read((void*) CurrentOffset, &NextOffset, size);
    }
    return CurrentOffset;
}
addr_type Memory::readEntity(addr_type EntAddress, addr_type ValueOffset, size_t size) {
    addr_type entity = 0;
    int value = 0;

    ///Ex: read entity ptr from list
    read((void*) EntAddress, &entity, sizeof(addr_type));
    ///Add offset to result Ex: +0x138 for health
    ///Read value at offset Ex: Health
    read((void*) (entity + ValueOffset), &value, size);
    ///Voila!
    return value;
}