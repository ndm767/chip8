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

Chip8::Chip8(std::string romPath, int scale){
    d = new Display(&running, scale);
    insProc = new InsProcessor(&memory[0], &V[0], &VI, &PC, &SP, &stack[0], &DT, &ST, d);

    //store bitmap font in memory range 0x000-0x050
    uchar font[80] = {
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

    //initialize the stack pointer to no value
    SP = static_cast<uchar>(16);

    //make the emulator loop
    running = true;

    //initialize registers to 0
    for(int i = 0; i<=0xF; i++){
        V[i] = 0;
    }

    //timers
    DT = 0;
    ST = 0;
}

Chip8::~Chip8(){
    delete insProc;
    delete d;
}

void Chip8::run(){
    while(running){
        d->startFrame();
        uchar byte1 = memory[PC];
        uchar byte2 = memory[PC+1];
        
        processInstructions(byte1, byte2);

        if(PC > 0xFFF){
            running = false;
        }

        PC += 2;
        //update timer
        if(DT != 0){
            DT -= 1;
        }
        if(ST != 0){
            ST -= 1;
        }

        d->endFrame();
    }   
}

void Chip8::processInstructions(uchar byte1, uchar byte2){

    usint bytes[] = {
        static_cast<usint>((byte1>>4)&0xF),
        static_cast<usint>(byte1&0xF),
        static_cast<usint>((byte2>>4)&0xF),
        static_cast<usint>(byte2 & 0xF)
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

usint Chip8::c2u(char c){
    usint t = static_cast<usint>(c);
    if(c >= 48 && c <= 57)
        return t - 48;
    if( c >= 65 && c <= 70)
        return t - 55;
    return t;
}

bool Chip8::compBytes(usint bytes[4], std::string instr){
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

void Chip8::handle0(usint bytes[4]){
    if(compBytes(bytes, "00E0")){
        insProc->cls00E0();
    }else if(compBytes(bytes, "00EE")){
        insProc->ret00EE();
    }else if(compBytes(bytes, "0nnn")){
        //supposedly ignored by modern interpreters
        std::cout<<"0nnn"<<std::endl;
    }
}

void Chip8::handle1(usint bytes[4]){
    //we already know its 1nnn
    usint addr = ((bytes[1]&0xF)<<8) + ((bytes[2]&0xF)<<4) + (bytes[3]&0xF);
    insProc->jp1nnn(addr);
}

void Chip8::handle2(usint bytes[4]){
    //we already know its 2nnn
    usint addr = ((bytes[1]&0xF)<<8) + ((bytes[2]&0xF)<<4) + (bytes[3]&0xF);
    insProc->call2nnn(addr);
}

void Chip8::handle3(usint bytes[4]){
    //we already know its 3xkk
    uchar reg = bytes[1]&0xF;
    uchar b = ((bytes[2]&0xF)<<4)+(bytes[3]&0xF);
    insProc->se3xkk(reg, b);
}

void Chip8::handle4(usint bytes[4]){
    //we already know its 4xkk
    uchar reg = bytes[1]&0xF;
    uchar b = ((bytes[2]&0xF)<<4)+(bytes[3]&0xF);
    insProc->sne4xkk(reg, b);
}

void Chip8::handle5(usint bytes[4]){
    if(compBytes(bytes, "5xy0")){
        uchar reg1 = bytes[1]&0xF;
        uchar reg2 = bytes[2]&0xF;
        insProc->se5xy0(reg1, reg2);
    }
}

void Chip8::handle6(usint bytes[4]){
    //we already know its 6xkk
    uchar reg = bytes[1]&0xF;
    uchar b = ((bytes[2]&0xF)<<4)+(bytes[3]&0xF);
    insProc->ld6xkk(reg, b);
}

void Chip8::handle7(usint bytes[4]){
    //we already know its 7xkk
    uchar reg = bytes[1]&0xF;
    uchar b = ((bytes[2]&0xF)<<4)+(bytes[3]&0xF);
    insProc->add7xkk(reg, b);
}

void Chip8::handle8(usint bytes[4]){
    uchar reg1 = bytes[1]&0xF;
    uchar reg2 = bytes[2]&0xF;
    if(compBytes(bytes, "8xy0")){
        insProc->ld8xy0(reg1, reg2);
    }else if(compBytes(bytes, "8xy1")){
        insProc->or8xy1(reg1, reg2);
    }else if(compBytes(bytes, "8xy2")){
        insProc->and8xy2(reg1, reg2);
    }else if(compBytes(bytes, "8xy3")){
        insProc->xor8xy3(reg1, reg2);
    }else if(compBytes(bytes, "8xy4")){
        insProc->add8xy4(reg1, reg2);
    }else if(compBytes(bytes, "8xy5")){
        insProc->sub8xy5(reg1, reg2);
    }else if(compBytes(bytes, "8xy6")){
        insProc->shr8xy6(reg1, reg2);
    }else if(compBytes(bytes, "8xy7")){
        insProc->subn8xy7(reg1, reg2);
    }else if(compBytes(bytes, "8xyE")){
        insProc->shl8xyE(reg1, reg2);
    }

}

void Chip8::handle9(usint bytes[4]){
    if(compBytes(bytes, "9xy0")){
        uchar reg1 = bytes[1]&0xF;
        uchar reg2 = bytes[2]&0xF;
        insProc->sne9xy0(reg1, reg2);
    }
}

void Chip8::handleA(usint bytes[4]){
    //we already know its Annn
    usint addr = ((bytes[1]&0xF)<<8) + ((bytes[2]&0xF)<<4) + (bytes[3]&0xF);
    insProc->ldAnnn(addr);
}

void Chip8::handleB(usint bytes[4]){
    //we already know its Bnnn
    usint addr = ((bytes[1]&0xF)<<8) + ((bytes[2]&0xF)<<4) + (bytes[3]&0xF);
    insProc->jpBnnn(addr);
}

void Chip8::handleC(usint bytes[4]){
    //we already know its Cxkk
    uchar reg = bytes[1]&0xF;
    uchar b = ((bytes[2]&0xF)<<4)+(bytes[3]&0xF);
    insProc->rndCxkk(reg, b);
}

void Chip8::handleD(usint bytes[4]){
    //we already know its Dxyn
    uchar reg1 = bytes[1]&0xF;
    uchar reg2 = bytes[2]&0xF;
    uchar nibble = bytes[3]&0xF;
    insProc->drwDxyn(reg1, reg2, nibble);
}

void Chip8::handleE(usint bytes[4]){
    uchar reg = bytes[1]&0xF;
    if(compBytes(bytes, "Ex9E")){
        insProc->skpEx9E(reg);
    }else if(compBytes(bytes, "ExA1")){
        insProc->sknpExA1(reg);
    }
}

void Chip8::handleF(usint bytes[4]){
    uchar reg = bytes[1]&0xF;
    if(compBytes(bytes, "Fx07")){
        insProc->ldFx07(reg);
    }
    if(compBytes(bytes, "Fx0A")){
        insProc->ldFx0A(reg);
    }
    if(compBytes(bytes, "Fx15")){
        insProc->ldFx15(reg);
    }
    if(compBytes(bytes, "Fx18")){
        insProc->ldFx18(reg);
    }
    if(compBytes(bytes, "Fx1E")){
        insProc->addFx1E(reg);
    }
    if(compBytes(bytes, "Fx29")){
        insProc->ldFx29(reg);
    }
    if(compBytes(bytes, "Fx33")){
        insProc->ldFx33(reg);
    }
    if(compBytes(bytes, "Fx55")){
        insProc->ldFx55(reg);
    }
    if(compBytes(bytes, "Fx65")){
        insProc->ldFx65(reg);
    }
}
