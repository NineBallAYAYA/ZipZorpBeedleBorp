//
// Created by root on 7/8/20.
//

#include "Keybinds.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include "iostream"
#include "boost/thread.hpp"
#include "map"

void Keybinds::open_keyboard() {
    fdK = open("/dev/input/event16", O_RDONLY | O_NONBLOCK);
    if (fdK == -1) {
        printf("Need to run as root!\n");
        exit(1);
    }
}

void Keybinds::open_mouse() {
    fdM = open("/dev/input/event4", O_RDONLY | O_NONBLOCK);
    if (fdM == -1) {
        printf("Need to run as root!\n");
        exit(1);
    }
}

Keybinds::Keybinds(BunnyHop *bunnyHop_) {
    bunnyhop = bunnyHop_;
}

void Keybinds::read_input() {
    std::map<unsigned int, bool> holdingKey;

    while (true) {
        usleep(50);
        struct input_event ie;
        int bytes = read(fdK, &ie, sizeof(ie));
        if (bytes > 0 && ie.type == EV_KEY && ie.value == 1) {
            if (ie.code == bhopkey) {
                holdingKey[bhopkey] = 1;
                bunnyhop->check();
            }
        } else if (bytes > 0 && ie.type == EV_KEY && ie.value == 0) {
            if (ie.code == bhopkey) {
                holdingKey[bhopkey] = 0;
                std::cout << holdingKey[bhopkey];
            }
        } else if (holdingKey[bhopkey] == 1) {
            bunnyhop->check();
        }

    }
}

void Keybinds::start_logging() {
    boost::thread t(&Keybinds::read_input, this);
}

void Keybinds::readMouse() {
    int bytes = read(fdK, &ie, sizeof(ie));
    if (bytes > 0 && ie.type == EV_KEY) {
        if(ie.value == 1){
            std::cout << "Pressed: " << ie.code << std::endl;

        } else{
            std::cout << "let go: " << ie.code << std::endl;
        }
    }

}
void Keybinds::sendMouse() {
    struct input_event ie;
  //  ie.type = EV_KEY;
  //  ie.code = KEY
   // write(fdM, &ie, sizeof(ie));

}