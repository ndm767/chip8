#include "display.h"

Display::Display(bool *r){
    running = r;
    scale = 10;
    for(int x = 0; x<64; x++){
        for(int y = 0; y<32; y++){
            pixels[x][y] = 0;
        }
    }

    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64*scale, 32*scale, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
}

Display::~Display(){

}

void Display::startFrame(){
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);

    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            *running = false;
        }else if(e.type == SDL_KEYDOWN){
            if(e.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                *running = false;
            }
        }
    }
}

void Display::endFrame(){
    for(int x = 0; x<64; x++){
        for(int y = 0; y<32; y++){
            if(pixels[x][y] != 0){
                SDL_Rect temp = {x*scale, y*scale, scale, scale};
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                SDL_RenderFillRect(gRenderer, &temp);
            }
        }
    }

    SDL_RenderPresent(gRenderer);
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