#include "insProcessor.h"

#include <iostream>

InsProcessor::InsProcessor(uchar *mem, uchar *V, usint *VI, usint *PC, uchar *SP, usint *stack, uchar* DT, uchar *ST, Display *d){
    this->memory = mem;
    this->V = V;
    this->VI = VI;
    this->PC = PC;
    this->SP = SP;
    this->stack = stack;
    this->DT = DT;
    this->ST = ST;
    this->display = d;
}

InsProcessor::~InsProcessor(){

}

/* PREFIX 0 */

void InsProcessor::cls00E0(){
    //clear display
    display->clear();
    //std::cout<<"00E0"<<std::endl;
}

void InsProcessor::ret00EE(){
    //return from subroutine
    //set program counter to value at top of stack
    *PC = *(stack + (*SP));
    //subtact one from stack pointer
    (*SP) -= 1;
    //std::cout<<"00EE"<<std::endl;
}

/* PREFIX 1 */

void InsProcessor::jp1nnn(usint addr){
    //jump to location addr-2 (because the PC increments by 2 at the end of each loop)
    (*PC) = addr-2;
    //std::cout<<"1nnn"<<std::endl;
}

/* PREFIX 2 */

void InsProcessor::call2nnn(usint addr){
    //call subroutine at addr
    //increment stack pointer
    if(*SP == static_cast<uchar>(16)){
        *SP = static_cast<uchar>(0);
    }else{
        *SP += 1;
    }
    //put current program counter at top of stack
    *(stack + (*SP)) = (*PC);
    //set program counter to new address
    (*PC) = addr-2;
    //std::cout<<"2nnn"<<std::endl;
}

/* PREFIX 3 */

void InsProcessor::se3xkk(uchar reg, uchar byte){
    //skip next instruction if v[reg] == byte
    if(*(V+reg) == byte){
        *(PC) += 2;
    }
    //std::cout<<"3xkk"<<std::endl;
}

/* PREFIX 4 */

void InsProcessor::sne4xkk(uchar reg, uchar byte){
    //skip next instruction if v[reg] != byte
    if(*(V+reg) != byte){
        *(PC) += 2;
    }
    //std::cout<<"4xkk"<<std::endl;
}

/* PREFIX 5 */

void InsProcessor::se5xy0(uchar reg1, uchar reg2){
    //skip next instruction if V[reg1] == V[reg2]
    if(*(V+reg1) == *(V+reg2)){
        *(PC) += 2;
    }
    //std::cout<<"5xy0"<<std::endl;
}

/* PREFIX 6 */

void InsProcessor::ld6xkk(uchar reg, uchar byte){
    //set v[reg] = byte
    *(V + reg) = byte;
    //std::cout<<"6xkk"<<std::endl;
}

/* PREFIX 7 */

void InsProcessor::add7xkk(uchar reg, uchar byte){
    // v[reg] += byte
    *(V + reg) += byte;
    //std::cout<<"7xkk"<<std::endl;
}

/* PREFIX 8 */

void InsProcessor::ld8xy0(uchar reg1, uchar reg2){
    //set v[reg1] = v[reg2]
    *(V + reg1) = *(V + reg2);
    //std::cout<<"8xy0"<<std::endl;
}

void InsProcessor::or8xy1(uchar reg1, uchar reg2){
    //v[reg1] = v[reg1] OR v[reg2]
    *(V + reg1) = *(V+reg1) | *(V+reg2);
    //std::cout<<"8xy1"<<std::endl;
}

void InsProcessor::and8xy2(uchar reg1, uchar reg2){
    //v[reg1] = v[reg1] AND v[reg2]
    *(V+reg1) = *(V+reg1) & *(V+reg2);
    //std::cout<<"8xy2"<<std::endl;
}

void InsProcessor::xor8xy3(uchar reg1, uchar reg2){
    //v[reg1] = v[reg1] XOR v[reg2]
    *(V+reg1) = *(V+reg1) ^ *(V+reg2);
    //std::cout<<"8xy3"<<std::endl;
}

void InsProcessor::add8xy4(uchar reg1, uchar reg2){
    //v[reg1] += v[reg2], v[f] carry
    usint t = *(V+reg1) + *(V + reg2);
    if(t > 255){
        *(V + 0xF) = 1;
    }
    *(V+reg1) = static_cast<uchar>(t&0xFF);
    //std::cout<<"8xy4"<<std::endl;
}

void InsProcessor::sub8xy5(uchar reg1, uchar reg2){
    //v[reg1] -= v[reg2], v[f] = not borrow
    //set borrow flag
    //TODO check if this is right
    if(*(V + reg1) >= *(V+reg2)){
        *(V + 0xF) = 1;
    }else{
        *(V+0xF) = 0;
    }
    std::cout<<static_cast<int>(*(V+reg1))<<" "<<static_cast<int>(*(V+reg2))<<" "<<static_cast<int>(*(V+0xF))<<std::endl;;
    //Subtract with carry
    *(V+reg1) = *(V+reg1) - (*(V+reg2));
    std::cout<<static_cast<int>(*(V+reg1))<<std::endl;;
    //std::cout<<"8xy5"<<std::endl;
}

void InsProcessor::shr8xy6(uchar reg1, uchar reg2){
    //v[reg1] = v[reg1] SHR 1 a.k.a v[reg1] >> 1
    //store least significant bit in V[f]
    uchar lsb = *(V+reg1)&0x1;
    *(V + 0xF) = lsb;
    *(V + reg1) = *(V+reg1)/2;
    //std::cout<<"8xy6"<<std::endl;
}

void InsProcessor::subn8xy7(uchar reg1, uchar reg2){
    //v[reg1] = v[reg2]-v[reg1], vf = not borrow
    //set borrow flag
    if(*(V + reg2) > *(V+reg1)){
        *(V + 0xF) = 1;
    }
    //Subtract with carry
    *(V+reg1) = *(V+reg2) + (~*(V+reg1)) + *(V+0xF);
    //std::cout<<"8xy7"<<std::endl;
}

void InsProcessor::shl8xyE(uchar reg1, uchar reg2){
    //v[reg1] = v[reg1] SHL 1 a.k.a v[reg1] << 1
    //store most significant bit in V[f]
    uchar msb = (*(V+reg1)>>7)&0x1;
    *(V + 0xF) = msb;
    *(V + reg1) = *(V+reg1)*2;
    //std::cout<<"8xyE"<<std::endl;

}

/* PREFIX 9 */

void InsProcessor::sne9xy0(uchar reg1, uchar reg2){
    //skip next instruction if v[reg1] != v[reg2]
    if(*(V+reg1) != *(V+reg2)){
        *PC += 2;
    }
    //std::cout<<"9xy0"<<std::endl;
}

/* PREFIX A */

void InsProcessor::ldAnnn(usint addr){
    //set VI = addr
    *VI = addr&0xFFF;
    //std::cout<<"Annn"<<std::endl;
}

/* PREFIX B */

void InsProcessor::jpBnnn(usint addr){
    //jump to location addr+v[0]
    //minus 2 to account for the PC incrementing at the end of this emulation cycle
    *PC = addr + *(V) - 2;
    //std::cout<<"Bnnn"<<std::endl;
}

/* PREFIX C */

void InsProcessor::rndCxkk(uchar reg, uchar byte){
    //set v[reg] = randomByte AND byte
    //std::cout<<"Cxkk"<<std::endl;
}

/* PREFIX D */

void InsProcessor::drwDxyn(uchar reg1, uchar reg2, uchar n){
    //display n-byte sprite starting at memory location VI at (V[reg1], V[reg2]), set VF = collision
    int x = *(V+reg1);
    int y = *(V+reg2);
    for(uchar i = 0; i<n; i++){
        uchar curr = *(memory + *VI + i);
        for(int j = 0; j<8; j++){
            int val = (curr>>j)&0x1;
            int cX = x;
            int cY = y;
            //for screen wrapping
            if(cX > 64){
                cX -= 64;
            }else if(cX < 0){
                cX += 64;
            }
            if(cY > 64){
                cY -= 64;
            }else if(cY < 0){
                cY += 64;
            }
            display->xorAtPos(cX, cY, val);
            y++;
        }
        y = *(V+reg2);
        x++;
    }
    //std::cout<<"Dxyn"<<std::endl;
}

/* PREFIX E */

void InsProcessor::skpEx9E(uchar reg){
    //skip next instruction if key with value of v[reg] is pressed
    if(display->getKeyPress(static_cast<int>(*(V+reg)))){
        *PC += 2;
    }
    //std::cout<<"Ex9E"<<std::endl;
}

void InsProcessor::sknpExA1(uchar reg){
    //skip next instruction if key with value of v[reg] is not pressed
    if(!display->getKeyPress(static_cast<int>(*(V+reg)))){
        *PC += 2;
    } 
    //std::cout<<"ExA1"<<std::endl;
}

/* PREFIX F */

void InsProcessor::ldFx07(uchar reg){
    //set v[reg] = delay timer
    *(V+reg) = *DT;
    //std::cout<<"Fx07"<<std::endl;
}

void InsProcessor::ldFx0A(uchar reg){
    //wait for key press and set v[reg] = key value
    //repeat the instruction if the key is not pressed
    int k = display->getAnyKeyPress();
    if(k == -1){
        *PC -= 2;
    }else{
        *(V+reg) = k;
    }
    //std::cout<<"Fx0A"<<std::endl;
}

void InsProcessor::ldFx15(uchar reg){
    //set delay timer = v[reg];
    *DT = *(V+reg);
    //std::cout<<"Fx15"<<std::endl;
}

void InsProcessor::ldFx18(uchar reg){
    //set sound timer = v[reg];
    *ST = *(V+reg);
    //std::cout<<"Fx18"<<std::endl;
}

void InsProcessor::addFx1E(uchar reg){
    //VI += v[reg]
    *(VI) += *(V + reg);
    //std::cout<<"Fx1E"<<std::endl;
}

void InsProcessor::ldFx29(uchar reg){
    //set I = location of sprite of digit v[reg]
    uchar spr = *(V+reg);
    *VI = spr*5;
    //std::cout<<"Fx29"<<std::endl;
}

void InsProcessor::ldFx33(uchar reg){
    //store bcd representation of vx in memory locations I, I+1, I+2
    int num = static_cast<int>(*(V+reg));

    int hundreds = (num - num%100)/100;
    num = num%100;
    int tens = (num - num%10)/10;
    num = num%10;
    int ones = num;

    *(memory + *VI) = hundreds;
    *(memory + *VI + 1) = tens;
    *(memory + *VI + 2) = ones;
    //std::cout<<"Fx33"<<std::endl;
}

void InsProcessor::ldFx55(uchar reg){
    //store registers v[0]-v[x] in memory starting at I
    for(uchar i = 0; i<=reg; i++){
        *(memory + *VI + i) = *(V+i);
    }
    //std::cout<<"Fx55"<<std::endl;
}

void InsProcessor::ldFx65(uchar reg){
    //read registers v[0]-v[x] from memory starting at location I
    for(uchar i = 0; i<= reg; i++){
        *(V+i) = *(memory + *VI + i);
    }
    //std::cout<<"Fx65"<<std::endl;
}