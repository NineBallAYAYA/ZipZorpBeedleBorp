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
#include "Misc.h"
#include "regex"

//Device id, File Descriptor
void Keybinds::init() {

    std::string s = GetStdoutFromCommand("ls /dev/input/");
    std::regex e("event(\\d+)");
    std::smatch m;
    while (std::regex_search(s, m, e)) {
        std::string a = m[1].str();
        deviceList.push_back(stoi(a));
        s = m.suffix().str();
    }
    for (int i = 0; i < deviceList.size(); i++) {
        std::string deviceFile = "/dev/input/event" + std::to_string(deviceList[i]);
        int fd = open(deviceFile.c_str(), O_RDONLY | O_NONBLOCK);
        if (fd == -1) {
            fprintf(stderr, "Need to run as root!");
            exit(1);
        }
        deviceFD[deviceList[i]] = fd;
    }
    read_input();
}


void Keybinds::read_input() {

    while (InputDeviceID == NULL) {
        for (int i = 0; i < deviceList.size(); i++) {
            struct input_event ie;
            int bytes = read(deviceFD[deviceList[i]], &ie, sizeof(ie));
            if (bytes > 0 && ie.type == EV_KEY && ie.value == 1 && (ie.code == bhopkey || ie.code == triggerkey)) {
                std::cout << "Input Device Found! id: " << i << std::endl;
                InputDeviceID = i;
                std::cout << "BHop Key: " << bhopkey << std::endl;
                std::cout << "Trigger Key: " << triggerkey << std::endl;
            }
        }
    }
    std::map<unsigned int, bool> holdingKey;
    while (true) {
        usleep(100);
        struct input_event ie;
        int bytes = read(deviceFD[deviceList[InputDeviceID]], &ie, sizeof(ie));
        if (bytes > 0 && ie.type == EV_KEY && ie.value == 1) {
            if (ie.code == bhopkey) {
                holdingKey[bhopkey] = 1;
                bunnyhop->check();
            }
            if (ie.code == triggerkey) {
                holdingKey[triggerkey] = 1;
                trigger->check();
            }
            if (ie.code == espkey) {
                esp->espOn == 0 ? esp->espOn = 1 : esp->espOn = 0;
            }
        } else if (bytes > 0 && ie.type == EV_KEY && ie.value == 0) {
            if (ie.code == bhopkey) {
                holdingKey[bhopkey] = 0;
            }
            if (ie.code == triggerkey) {
                holdingKey[triggerkey] = 0;
            }
        }
        if (holdingKey[bhopkey] == 1) {
            bunnyhop->check();
        }
        if (holdingKey[triggerkey] == 1) {
            trigger->check();
        }


    }
}


Keybinds::Keybinds(BunnyHop *bunnyHop_, Trigger *trigger_, Esp* esp_) {
    bunnyhop = bunnyHop_;
    trigger = trigger_;
    esp = esp_;
}
