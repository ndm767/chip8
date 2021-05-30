#pragma once

#include <string>

typedef unsigned char uchar;
typedef unsigned short int usint;

class Chip8{
public:
    Chip8(std::string romPath);
    ~Chip8();

    void run();
private:
    void loadRom(std::string rom, int start);

    void processInstructions(uchar byte1, uchar byte2);

    uchar memory[0xFFF+1];

    uchar V[16]; //registers
    usint VI; //16 bit register

    usint PC; //program counter
    
    uchar SP; //stack pointer
    usint stack[16]; //stack

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

    //actual opcode instructions
    //prefix 0
    void cls(); //clear display
    void ret(); //return from subroutine
    
    //prefix 1
    void jp(usint addr); //jump to location addr

    //prefix 2
    void call(usint addr); //call subroutine at addr

    //prefix 3
    void se3xkk(uchar reg, uchar byte); //skip next instruction if v[reg] == byte

    //prefix 4
    void sne4xkk(uchar reg, uchar byte); //skip next instruction if v[reg] != byte

    //prefix 5
    void se5xy0(uchar reg1, uchar reg2); //skip next instruction if V[reg1] == V[reg2]

    //prefix 6
    void ld6xkk(uchar reg, uchar byte); //set v[reg] = byte

};