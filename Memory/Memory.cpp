//
// Created by nate on 7/7/20.
//

#include "Memory.h"
#include <regex>

//Probably a more efficent way to do this but whatever....
std::string GetStdoutFromCommand(std::string cmd) {
    std::string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");
    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
        pclose(stream);
    }
    return data;
}

//Fairly straightforward
void Memory::getPid(const std::string& procName) {
    std::string cmd = "pidof -s " + procName;
    std::string pidStr = GetStdoutFromCommand(cmd);
    pid = std::stoi(pidStr);
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
    base_player_addr =  clientAddr.first  +  base_player_offset;
    force_jump_addr  =  clientAddr.first  +  force_jump_offset;
    std::vector<addr_type> offsets(2);
    offsets[0] = base_player_addr;
    offsets[1] = flags_offset;
    flags_addr = multiLevelPointer(offsets, 8);
}

addr_type Memory::multiLevelPointer(std::vector<addr_type> offsets, size_t size) {
    addr_type NextOffset = 0;
    addr_type CurrentOffset = 0;
    for (int i = 0; i < offsets.size(); i++){
        CurrentOffset = offsets[i] + NextOffset;
        read((void*) CurrentOffset, &NextOffset, sizeof(CurrentOffset));
    }
    return CurrentOffset;
}
