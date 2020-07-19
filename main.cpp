#include "Memory/Memory.h"
#include "Hacks/BunnyHop.h"
#include "Hacks/Trigger.h"
#include "Hacks/Esp.h"
#include "misc/Keybinds.h"
#include <unistd.h>
#include <boost/thread.hpp>
#include "iostream"
#include "map"

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
        memory.getClientModule();
        usleep(100);
    }
    std::cout << "Found Client Module At: " << memory.clientAddr.first << std::endl;
    memory.RefreshAddr();
//------------------------------------------------------------------------------------//
  BunnyHop   bunnyHop(&memory);
  Trigger    trigger(&memory);
  Keybinds   keyBinds(&bunnyHop, &trigger);
  //Esp        esp(&memory);
    keyBinds.init();


  while(true){
      usleep(1000000);
  }
}
