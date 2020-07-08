#include "Memory/Memory.h"
#include "Hacks/BunnyHop.h"
#include <unistd.h>

int main() {
//------------------------------------------------------------------------------------//
//Spawn the different hacks for possible use
    Memory Memory;
    BunnyHop BunnyHop(&Memory);

//------------------------------------------------------------------------------------//
//Initialise
    while(!Memory.pid){
        Memory.getPid("csgo_linux64");
        usleep(100);
    }
    std::cout << "Found Process, PID: " << Memory.pid << std::endl;
    while(!Memory.clientAddr.first) {
        Memory.getClientModule();
        usleep(100);
    }
    std::cout << "Found Client Module At: " << Memory.clientAddr.first << std::endl;
    Memory.RefreshAddr();
//------------------------------------------------------------------------------------//

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
