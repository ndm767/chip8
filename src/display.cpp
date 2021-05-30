#include "display.h"

Display::Display(){
    int scale = 1;
    scale *= 1;
    for(int x = 0; x<64; x++){
        for(int y = 0; y<32; y++){
            pixels[x][y] = 0;
        }
    }
}

Display::~Display(){

}

void Display::startFrame(){

}

void Display::endFrame(){

}

void Display::clear(){
    for(int x = 0; x<64; x++){
        for(int y = 0; y<32; y++){
            pixels[x][y] = 0;
        }
    }
}

int Display::xorAtPos(int x, int y, int val){
    int oldPix = pixels[x][y];
    pixels[x][y] = pixels[x][y] ^ val;
    //return 1 if pixel goes from 1 to 0
    if(oldPix == 1 && oldPix != pixels[x][y]){
        return 1;
    }
    return 0;
}