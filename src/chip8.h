#pragma once

#include <string>

typedef unsigned char uchar;

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
    unsigned short int VI; //16 bit register

    unsigned short int PC; //program counter
    
    uchar SP; //stack pointer
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

    //actual opcode instructions
    //prefix 0
    void cls(); //clear display
    void ret(); //return from subroutine
    
    //prefix 1
    void jp(unsigned int addr); //jump to location addr

    //prefix 2
    void call(unsigned int addr); //call subroutine at addr

    //prefix 3
    void se3xkk(uchar reg, uchar byte); //skip next instruction if v[reg] == byte

    //prefix 4
    void sne4xkk(uchar reg, uchar byte); //skip next instruction if v[reg] != byte

    //prefix 5
    void se5xy0(uchar reg1, uchar reg2); //skip next instruction if V[reg1] == V[reg2]

    //prefix 6
    void ld6xkk(uchar reg, uchar byte); //set v[reg] = byte

};