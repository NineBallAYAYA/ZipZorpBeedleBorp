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
  Keybinds   keyBinds(&bunnyHop);
  //Esp        esp(&memory);
  Trigger    trigger(&memory);

  keyBinds.open_keyboard();
  keyBinds.open_mouse();
  keyBinds.start_logging();

 // esp.cycleEntitys();
  // boost::function<void(unsigned int)> bhopFunc = boost::bind(&BunnyHop::check, &bunnyHop, _1);
  // keyBinds.bind("I", bhopFunc);
  // keyBinds.startListen();
    while(true){
        trigger.check();
        usleep(10*1000);
    //    keyBinds.readMouse();
    };
  //while(Process is open){
  //    if(BunnyHopToggleON){
  //        BunnyHop.check();
  //    }
  //
  //    if(AimToggleON){
  //        Aim.AimUpdate();
  //    }
  //
  //    if(AntiFlashOn){
  //        AFlash.update();
  //    }
  //
  //    usleep(100);
  //}
}
