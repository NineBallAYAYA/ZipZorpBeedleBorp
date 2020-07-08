cmake_minimum_required(VERSION 3.16)
project(MultiHack)
#file(GLOB_RECURSE Sources "*.c" "*.cpp" "*.hpp" )

set(CMAKE_CXX_STANDARD 20)

add_executable(MultiHack main.cpp Memory/Memory.cpp Memory/Memory.h Hacks/BunnyHop.cpp Hacks/BunnyHop.h misc/typedef.h)