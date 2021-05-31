#include <iostream>

#include "chip8.h"

//TODO
//Make 60hz
//Implement sound

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cout<<"Not enough arguments! Expected file path!"<<std::endl;
        std::terminate();
    }

    std::string romPath(argv[1]);

    Chip8 emu(romPath);
    emu.run();

    return 0;
}