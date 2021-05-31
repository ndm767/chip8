#include <iostream>

#include "chip8.h"

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cout<<"Not enough arguments! Expected file path!"<<std::endl;
        std::terminate();
    }

    std::string romPath(argv[1]);
    int emuscale = 10;

    if(argc == 4){
        if(strcmp(argv[1], "-s") == 0){
            emuscale = atoi(argv[2]);
            romPath = std::string(argv[3]);
        }else if(strcmp(argv[2], "-s") == 0){
            emuscale = atoi(argv[3]);
            romPath = std::string(argv[1]);
        }
    }

    Chip8 emu(romPath, emuscale);
    emu.run();

    return 0;
}