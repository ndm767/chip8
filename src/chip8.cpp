#include "chip8.h"

#include <iostream>
#include <fstream>
#include <sstream>

void Chip8::loadRom(std::string rom){
    std::ifstream f(rom, std::ios_base::in | std::ios_base::binary);

    if(!f){
        std::cout<<"Could not open ROM: "<<rom<<std::endl;
        std::terminate();
    }

    std::stringstream ss;
    ss << f.rdbuf();
    std::string file = ss.str();

    const char* insStr = file.c_str();
    std::size_t fSize = file.size();
    if(fSize > 0xFFF){
        std::cout<<"Rom "<<rom<<" is too big to load into memory! It is "<<fSize<<" bytes!"<<std::endl;
        std::terminate();
    }

    for(int i = 0; i<fSize; i++){
        *(memory + 0x200 + i) = insStr[i];
    }
}

Chip8::Chip8(std::string romPath){
    memory = new unsigned char[0xFFF+1];

    loadRom(romPath);
}

Chip8::~Chip8(){
    delete[] memory;
}

