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

    void handle0(unsigned int bytes[4]);
    void handle1(unsigned int bytes[4]);
    void handle2(unsigned int bytes[4]);
    void handle3(unsigned int bytes[4]);
    void handle4(unsigned int bytes[4]);
    void handle5(unsigned int bytes[4]);
    void handle6(unsigned int bytes[4]);
    void handle7(unsigned int bytes[4]);
    void handle8(unsigned int bytes[4]);
    void handle9(unsigned int bytes[4]);
    void handleA(unsigned int bytes[4]);
    void handleB(unsigned int bytes[4]);
    void handleC(unsigned int bytes[4]);
    void handleD(unsigned int bytes[4]);
    void handleE(unsigned int bytes[4]);
    void handleF(unsigned int bytes[4]);

    //utility functions
    bool compBytes(unsigned int bytes[4], std::string instr);
    unsigned int c2u(char c);
};