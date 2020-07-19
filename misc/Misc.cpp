//
// Created by root on 7/8/20.
//

#include "Misc.h"


std::string GetStdoutFromCommand(std::string cmd) {
    std::string data;
    FILE * stream;
    const int max_buffer = 8000;
    char buffer[max_buffer];
    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
        pclose(stream);
    }
    return data;
}