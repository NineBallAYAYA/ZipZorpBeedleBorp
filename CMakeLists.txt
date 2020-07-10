cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)


#---------------------------------------------------------#
#Build
project(MultiHack)
add_executable(MultiHack main.cpp Memory/Memory.cpp Memory/Memory.h Hacks/BunnyHop.cpp Hacks/BunnyHop.h misc/typedef.h misc/Keybinds.cpp misc/Keybinds.h misc/Misc.h misc/Misc.cpp Hacks/Esp.cpp Hacks/Esp.h Hacks/Trigger.cpp Hacks/Trigger.h)
#---------------------------------------------------------#
#Link boost
find_package(Boost COMPONENTS thread system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(MultiHack ${Boost_LIBRARIES})
#---------------------------------------------------------#
#Link X11
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
target_link_libraries(MultiHack "-lX11" )
#---------------------------------------------------------#

