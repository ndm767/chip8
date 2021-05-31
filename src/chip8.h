#pragma once

#include <string>
#include "display.h"
#include "insProcessor.h"

class Chip8{
public:
    Chip8(std::string romPath, int scale);
    ~Chip8();

    void run();
private:
    void loadRom(std::string rom, int start);

    void processInstructions(uchar byte1, uchar byte2);

    InsProcessor *insProc;
    Display *d;

    uchar memory[0xFFF+1];

    uchar V[16]; //registers
    usint VI; //16 bit register

    usint PC; //program counter
    
    uchar SP; //stack pointer
    usint stack[16]; //stack

    uchar DT; //delay timer
    uchar ST; //sound timer

    bool running;

    void handle0(usint bytes[4]);
    void handle1(usint bytes[4]);
    void handle2(usint bytes[4]);
    void handle3(usint bytes[4]);
    void handle4(usint bytes[4]);
    void handle5(usint bytes[4]);
    void handle6(usint bytes[4]);
    void handle7(usint bytes[4]);
    void handle8(usint bytes[4]);
    void handle9(usint bytes[4]);
    void handleA(usint bytes[4]);
    void handleB(usint bytes[4]);
    void handleC(usint bytes[4]);
    void handleD(usint bytes[4]);
    void handleE(usint bytes[4]);
    void handleF(usint bytes[4]);

    //utility functions
    bool compBytes(usint bytes[4], std::string instr);
    usint c2u(char c);
};