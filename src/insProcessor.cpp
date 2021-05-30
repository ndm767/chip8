#include "insProcessor.h"

#include <iostream>

InsProcessor::InsProcessor(uchar *mem, uchar *V, usint *VI, usint *PC, uchar *SP, usint *stack, Display *d){
    this->memory = mem;
    this->V = V;
    this->VI = VI;
    this->PC = PC;
    this->SP = SP;
    this->stack = stack;
    this->display = d;
}

InsProcessor::~InsProcessor(){

}

/* PREFIX 0 */

void InsProcessor::cls00E0(){
    //clear display
    display->clear();
    std::cout<<"00E0"<<std::endl;
}

void InsProcessor::ret00EE(){
    //return from subroutine
    //set program counter to value at top of stack
    *PC = *(stack + (*SP));
    //subtact one from stack pointer
    (*SP) -= 1;
    std::cout<<"00EE"<<std::endl;
}

/* PREFIX 1 */

void InsProcessor::jp1nnn(usint addr){
    //jump to location addr
    (*PC) = addr;
    std::cout<<"1nnn"<<std::endl;
}

/* PREFIX 2 */

void InsProcessor::call2nnn(usint addr){
    //call subroutine at addr
    std::cout<<"2nnn"<<std::endl;
}

/* PREFIX 3 */

void InsProcessor::se3xkk(uchar reg, uchar byte){
    //skip next instruction if v[reg] == byte
    std::cout<<"3xkk"<<std::endl;
}

/* PREFIX 4 */

void InsProcessor::sne4xkk(uchar reg, uchar byte){
    //skip next instruction if v[reg] != byte
    std::cout<<"4xkk"<<std::endl;
}

/* PREFIX 5 */

void InsProcessor::se5xy0(uchar reg1, uchar reg2){
    //skip next instruction if V[reg1] == V[reg2]
    std::cout<<"5xy0"<<std::endl;
}

/* PREFIX 6 */

void InsProcessor::ld6xkk(uchar reg, uchar byte){
    //set v[reg] = byte
    std::cout<<"6xkk"<<std::endl;
}

/* PREFIX 7 */

void InsProcessor::add7xkk(uchar reg, uchar byte){
    // v[reg] += byte
    std::cout<<"7xkk"<<std::endl;
}

/* PREFIX 8 */

void InsProcessor::ld8xy0(uchar reg1, uchar reg2){
    //set v[reg1] = v[reg2]
    std::cout<<"8xy0"<<std::endl;
}

void InsProcessor::or8xy1(uchar reg1, uchar reg2){
    //v[reg1] = v[reg1] OR v[reg2]
    std::cout<<"8xy1"<<std::endl;
}

void InsProcessor::and8xy2(uchar reg1, uchar reg2){
    //v[reg1] = v[reg1] AND v[reg2]
    std::cout<<"8xy2"<<std::endl;
}

void InsProcessor::xor8xy3(uchar reg1, uchar reg2){
    //v[reg1] = v[reg1] XOR v[reg2]
    std::cout<<"8xy3"<<std::endl;
}

void InsProcessor::add8xy4(uchar reg1, uchar reg2){
    //v[reg1] += v[reg2], v[f] carry
    std::cout<<"8xy4"<<std::endl;
}

void InsProcessor::sub8xy5(uchar reg1, uchar reg2){
    //v[reg1] -= v[reg2], v[f] = not borrow
    std::cout<<"8xy5"<<std::endl;
}

void InsProcessor::shr8xy6(uchar reg1, uchar reg2){
    //v[reg1] = v[reg1] SHR 1
    std::cout<<"8xy6"<<std::endl;
}

void InsProcessor::subn8xy7(uchar reg1, uchar reg2){
    //v[reg1] = v[reg2]-v[reg1], vf = not borrow
    std::cout<<"8xy7"<<std::endl;
}

void InsProcessor::shl8xyE(uchar reg1, uchar reg2){
    //v[reg1] = v[reg1] SHL 1
    std::cout<<"8xyE"<<std::endl;

}

/* PREFIX 9 */

void InsProcessor::sne9xy0(uchar reg1, uchar reg2){
    //skip next instruction if v[reg1] != v[reg2]
    std::cout<<"9xy0"<<std::endl;
}

/* PREFIX A */

void InsProcessor::ldAnnn(usint addr){
    //set VI = addr
    std::cout<<"Annn"<<std::endl;
}

/* PREFIX B */

void InsProcessor::jpBnnn(usint addr){
    //jump to location addr+v[0]
    std::cout<<"Bnnn"<<std::endl;
}

/* PREFIX C */

void InsProcessor::rndCxkk(uchar reg, uchar byte){
    //set v[reg] = randomByte AND byte
    std::cout<<"Cxkk"<<std::endl;
}

/* PREFIX D */

void InsProcessor::drwDxyn(uchar reg1, uchar reg2, uchar n){
    //display n-byte sprite starting at memory location VI at (V[reg1], V[reg2]), set VF = collision
    std::cout<<"Dxyn"<<std::endl;
}

/* PREFIX E */

void InsProcessor::skpEx9E(uchar reg){
    //skip next instruction if key with value of v[reg] is pressed
    std::cout<<"Ex9E"<<std::endl;
}

void InsProcessor::sknpExA1(uchar reg){
    //skip next instruction if key with value of v[reg] is not pressed 
    std::cout<<"ExA1"<<std::endl;
}

/* PREFIX F */

void InsProcessor::ldFx07(uchar reg){
    //set v[reg] = delay timer
    std::cout<<"Fx07"<<std::endl;
}

void InsProcessor::ldFx0A(uchar reg){
    //wait for key press and set v[reg] = key value
    std::cout<<"Fx0A"<<std::endl;
}

void InsProcessor::ldFx15(uchar reg){
    //set delay timer = v[reg];
    std::cout<<"Fx15"<<std::endl;
}

void InsProcessor::ldFx18(uchar reg){
    //set sound timer = v[reg];
    std::cout<<"Fx18"<<std::endl;
}

void InsProcessor::addFx1E(uchar reg){
    //VI += v[reg]
    std::cout<<"Fx1E"<<std::endl;
}

void InsProcessor::ldFx29(uchar reg){
    //set I = location of sprite of digit v[reg]
    std::cout<<"Fx29"<<std::endl;
}

void InsProcessor::ldFx33(uchar reg){
    //store bcd representation of vx in memory locations I, I+1, I+2
    std::cout<<"Fx33"<<std::endl;
}

void InsProcessor::ldFx55(uchar reg){
    //store registers v[0]-v[x] in memory starting at I
    std::cout<<"Fx55"<<std::endl;
}

void InsProcessor::ldFx65(uchar reg){
    //read registers v[0]-v[x] from memory starting at location I
    std::cout<<"Fx65"<<std::endl;
}