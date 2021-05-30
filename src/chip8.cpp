#include "chip8.h"

#include <iostream>
#include <fstream>
#include <sstream>

void Chip8::loadRom(std::string rom, int start){
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

    for(std::size_t i = 0; i<fSize; i++){
        *(memory + start + i) = insStr[i];
    }
}

Chip8::Chip8(std::string romPath){
    //store bitmap font in memory range 0x000-0x050
    unsigned char font[80] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, //0
        0x20, 0x60, 0x20, 0x20, 0x70, //1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
        0x90, 0x90, 0xF0, 0x10, 0x10, //4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
        0xF0, 0x10, 0x20, 0x40, 0x40, //7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
        0xF0, 0x90, 0xF0, 0x90, 0x90, //A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
        0xF0, 0x80, 0x80, 0x80, 0xF0, //C
        0xE0, 0x90, 0x90, 0x90, 0xE0, //D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
        0xF0, 0x80, 0xF0, 0x80, 0x80  //F
    };

    for(int i = 0; i<0x050; i++){
        memory[i] = font[i];
    }

    //most programs start at 0x200 but some start at 0x600
    loadRom(romPath, 0x200);
    PC = 0x200;

    //initialize the stack pointer to the bottom of the stack
    SP = static_cast<unsigned char>(0);

    //make the emulator loop
    running = true;
}

Chip8::~Chip8(){

}

void Chip8::run(){
    while(running){
        unsigned char byte1 = memory[PC];
        unsigned char byte2 = memory[PC+1];
        
        std::cout<<std::hex<<static_cast<int>(byte1)<<" "<<static_cast<int>(byte2)<<": ";
        processInstructions(byte1, byte2);

        if(PC > 0xFFF){
            running = false;
        }

        PC += 2;
    }   
}

void Chip8::processInstructions(unsigned char byte1, unsigned char byte2){

    unsigned int bytes[] = {
        static_cast<unsigned int>((byte1>>4)&0xF),
        static_cast<unsigned int>(byte1&0xF),
        static_cast<unsigned int>((byte2>>4)&0xF),
        static_cast<unsigned int>(byte2 & 0xF)
    };
    switch(bytes[0]){
        case 0x0:
            handle0(bytes);
            break;
        case 0x1:
            handle1(bytes);
            break;
        case 0x2:
            handle2(bytes);
            break;
        case 0x3:
            handle3(bytes);
            break;
        case 0x4:
            handle4(bytes);
            break;
        case 0x5:
            handle5(bytes);
            break;
        case 0x6:
            handle6(bytes);
            break;
        case 0x7:
            handle7(bytes);
            break;
        case 0x8:
            handle8(bytes);
            break;
        case 0x9:
            handle9(bytes);
            break;
        case 0xA:
            handleA(bytes);
            break;
        case 0xB:
            handleB(bytes);
            break;
        case 0xC:
            handleC(bytes);
            break;
        case 0xD:
            handleD(bytes);
            break;
        case 0xE:
            handleE(bytes);
            break;
        case 0xF:
            handleF(bytes);
            break;
        default:
            std::cout<<"Bad Opcode!"<<std::endl;
            break;
    }
}

unsigned int Chip8::c2u(char c){
    unsigned int t = static_cast<unsigned int>(c);
    if(c >= 48 && c <= 57)
        return t - 48;
    if( c >= 65 && c <= 70)
        return t - 55;
    return t;
}

bool Chip8::compBytes(unsigned int bytes[4], std::string instr){
    //compares a set of bytes to the instruction
    if(instr.length() != 4){
        return false;
    }
    const char* ins = instr.c_str();

    for(int i = 0; i<4; i++){
        if(c2u(ins[i]) != bytes[i]){
            //check if it isn't a placeholder character
            if(ins[i] != 'n' && ins[i] != 'x' && ins[i] != 'y' && ins[i] != 'k'){
                return false;
            }
        }
    }

    return true;
}

void Chip8::handle0(unsigned int bytes[4]){
    
}

void Chip8::handle1(unsigned int bytes[4]){
    
}

void Chip8::handle2(unsigned int bytes[4]){
    
}

void Chip8::handle3(unsigned int bytes[4]){
    
}

void Chip8::handle4(unsigned int bytes[4]){
    
}

void Chip8::handle5(unsigned int bytes[4]){
    
}

void Chip8::handle6(unsigned int bytes[4]){
    
}

void Chip8::handle7(unsigned int bytes[4]){
    
}

void Chip8::handle8(unsigned int bytes[4]){
    
}

void Chip8::handle9(unsigned int bytes[4]){
    
}

void Chip8::handleA(unsigned int bytes[4]){
    
}

void Chip8::handleB(unsigned int bytes[4]){
    
}

void Chip8::handleC(unsigned int bytes[4]){
    
}

void Chip8::handleD(unsigned int bytes[4]){
    
}

void Chip8::handleE(unsigned int bytes[4]){
    
}

void Chip8::handleF(unsigned int bytes[4]){
    
}