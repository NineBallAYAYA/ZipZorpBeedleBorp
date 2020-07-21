//
// Created by root on 7/8/20.
//

#ifndef MULTIHACK_ESP_H
#define MULTIHACK_ESP_H
#include "../Memory/Memory.h"
#include "boost/thread.hpp"

class Esp {
public:
    Esp(Memory* memory);
    void init();
    int espOn = 0;
private:
    boost::thread ESP;
    void cycleEntitys();
    void setColour(int index, float r, float g, float b, float a, bool Occluded, bool UnOccluded);
    Memory* memory;
};


#endif //MULTIHACK_ESP_H
