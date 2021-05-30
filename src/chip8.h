#pragma once

#include <string>

class Chip8{
public:
    Chip8(std::string romPath);
    ~Chip8();

    void run();
private:
    void loadRom(std::string rom, int start);

    void processInstructions(unsigned char byte1, unsigned char byte2);

    unsigned char memory[0xFFF+1];

    unsigned char V[16]; //registers
    unsigned short int VI; //16 bit register

    unsigned short int PC; //program counter
    
    unsigned char SP; //stack pointer
    unsigned short int stack[16]; //stack

    bool running;

    void handle0(unsigned char bytes[4]);
    void handle1(unsigned char bytes[4]);
    void handle2(unsigned char bytes[4]);
    void handle3(unsigned char bytes[4]);
    void handle4(unsigned char bytes[4]);
    void handle5(unsigned char bytes[4]);
    void handle6(unsigned char bytes[4]);
    void handle7(unsigned char bytes[4]);
    void handle8(unsigned char bytes[4]);
    void handle9(unsigned char bytes[4]);
    void handleA(unsigned char bytes[4]);
    void handleB(unsigned char bytes[4]);
    void handleC(unsigned char bytes[4]);
    void handleD(unsigned char bytes[4]);
    void handleE(unsigned char bytes[4]);
    void handleF(unsigned char bytes[4]);
};