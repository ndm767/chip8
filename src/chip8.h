#pragma once

#include <string>

class Chip8{
public:
    Chip8(std::string romPath);
    ~Chip8();

    void run();
private:
    void loadRom(std::string rom, int start);

    unsigned char memory[0xFFF+1];

    unsigned char V[16]; //registers
    unsigned short int VI; //16 bit register

    unsigned short int PC; //program counter
    
    unsigned char SP; //stack pointer
    unsigned short int stack[16]; //stack
};