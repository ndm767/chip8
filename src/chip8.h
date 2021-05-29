#pragma once

#include <string>

class Chip8{
public:
    Chip8(std::string romPath);
    ~Chip8();

private:
    void loadRom(std::string rom, int start);

    unsigned char* memory;
};