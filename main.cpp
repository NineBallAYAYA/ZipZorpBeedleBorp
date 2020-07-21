#include "Memory/Memory.h"
#include "Hacks/BunnyHop.h"
#include "Hacks/Trigger.h"
#include "Hacks/Esp.h"
#include "misc/Keybinds.h"
#include <unistd.h>
#include <boost/thread.hpp>
#include "iostream"

boost::thread CheckIfAddrValid;

int main() {
//------------------------------------------------------------------------------------//
//Spawn Memory as it is very core...
    Memory memory;
//------------------------------------------------------------------------------------//
//Initialise
    while(!memory.pid){
        memory.getPid("csgo_linux64");
        usleep(100);
    }
    std::cout << "Found Process, PID: " << memory.pid << std::endl;
    while(!memory.clientAddr.first) {
       memory.clientAddr = memory.getModule("client_client.so");
        usleep(100);
    }
    std::cout << "Found Client Module At: " << memory.clientAddr.first << std::endl;
//------------------------------------------------------------------------------------//
    while(!memory.engineAddr.first) {
        memory.engineAddr = memory.getModule("engine_client.so");
        usleep(100);
    }
    std::cout << "Found Engine Module At: " << memory.engineAddr.first << std::endl;

    memory.setAddr();
//------------------------------------------------------------------------------------//
  BunnyHop   bunnyHop(&memory);
  Trigger    trigger(&memory);
  Esp        esp(&memory);
  Keybinds   keyBinds(&bunnyHop, &trigger, &esp);

  CheckIfAddrValid = boost::thread(&Memory::checkIfValid, &memory);
  keyBinds.init();

}
