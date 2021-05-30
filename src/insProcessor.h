#pragma once

typedef unsigned char uchar;
typedef unsigned short int usint;

class InsProcessor{
private:
    uchar *memory;
    uchar *V;
    usint *VI;
    usint *PC;
    uchar *SP;
    usint *stack;
public:
    InsProcessor(uchar *mem, uchar *V, usint *VI, usint *PC, uchar *SP, usint *stack);
    ~InsProcessor();

    //actual opcode instructions
    //prefix 0
    void cls00E0(); //clear display
    void ret00EE(); //return from subroutine
    
    //prefix 1
    void jp1nnn(usint addr); //jump to location addr

    //prefix 2
    void call2nnn(usint addr); //call subroutine at addr

    //prefix 3
    void se3xkk(uchar reg, uchar byte); //skip next instruction if v[reg] == byte

    //prefix 4
    void sne4xkk(uchar reg, uchar byte); //skip next instruction if v[reg] != byte

    //prefix 5
    void se5xy0(uchar reg1, uchar reg2); //skip next instruction if V[reg1] == V[reg2]

    //prefix 6
    void ld6xkk(uchar reg, uchar byte); //set v[reg] = byte

    //prefix 7
    void add7xkk(uchar reg, uchar byte); // v[reg] += byte

    //prefix 8
    void ld8xy0(uchar reg1, uchar reg2); //set v[reg1] = v[reg2]
    void or8xy1(uchar reg1, uchar reg2); //v[reg1] = v[reg1] OR v[reg2]
    void and8xy2(uchar reg1, uchar reg2); //v[reg1] = v[reg1] AND v[reg2]
    void xor8xy3(uchar reg1, uchar reg2); //v[reg1] = v[reg1] XOR v[reg2]
    void add8xy4(uchar reg1, uchar reg2); //v[reg1] += v[reg2], v[f] carry
    void sub8xy5(uchar reg1, uchar reg2); //v[reg1] -= v[reg2], v[f] = not borrow
    void shr8xy6(uchar reg1, uchar reg2); //v[reg1] = v[reg1] SHR 1
    void subn8xy7(uchar reg1, uchar reg2); //v[reg1] = v[reg2]-v[reg1], vf = not borrow
    void shl8xyE(uchar reg1, uchar reg2); //v[reg1] = v[reg1] SHL 1

    //prefix 9
    void sne9xy0(uchar reg1, uchar reg2); //skip next instruction if v[reg1] != v[reg2]
    
    //prefix A
    void ldAnnn(usint addr); //set VI = addr

    //prefix B
    void jpBnnn(usint addr); //jump to location addr+v[0]

    //prefix C
    void rndCxkk(uchar reg, uchar byte); //set v[reg] = randomByte AND byte

    //prefix D
    void drwDxyn(uchar reg1, uchar reg2, uchar n); //display n-byte sprite starting at memory location VI at (V[reg1], V[reg2]), set VF = collision

    //prefix E
    void skpEx9E(uchar reg); //skip next instruction if key with value of v[reg] is pressed
    void sknpExA1(uchar reg); //skip next instruction if key with value of v[reg] is not pressed 

    //prefix F
    void ldFx07(uchar reg); //set v[reg] = delay timer
    void ldFx0A(uchar reg); //wait for key press and set v[reg] = key value
    void ldFx15(uchar reg); //set delay timer = v[reg];
    void ldFx18(uchar reg); //set sound timer = v[reg];
    void addFx1E(uchar reg); //VI += v[reg]
    void ldFx29(uchar reg); //set I = location of sprite of digit v[reg]
    void ldFx33(uchar reg); //store bcd representation of vx in memory locations I, I+1, I+2
    void ldFx55(uchar reg); //store registers v[0]-v[x] in memory starting at I
    void ldFx65(uchar reg); //read registers v[0]-v[x] from memory starting at location I
};