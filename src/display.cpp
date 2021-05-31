#include "display.h"

#include <thread>

Display::Display(bool *r, int s){
    running = r;
    scale = s;
    for(int x = 0; x<64; x++){
        for(int y = 0; y<32; y++){
            pixels[x][y] = 0;
        }
    }

    for(int i = 0; i<=0xF; i++){
        keysPressed[i] = false;
    }

    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64*scale, 32*scale, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
}

Display::~Display(){

}

void Display::startFrame(){
    startTime = std::chrono::high_resolution_clock::now();
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);

    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            *running = false;
        }else if(e.type == SDL_KEYDOWN){
            if(e.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                *running = false;
            }else{
                switch(e.key.keysym.scancode){
                case static_cast<int>(Keys::ZERO):
                    keysPressed[0] = true;
                    break;
                case static_cast<int>(Keys::ONE):
                    keysPressed[1] = true;
                    break;
                case static_cast<int>(Keys::TWO):
                    keysPressed[2] = true;
                    break;
                case static_cast<int>(Keys::THREE):
                    keysPressed[3] = true;
                    break;
                case static_cast<int>(Keys::FOUR):
                    keysPressed[4] = true;
                    break;
                case static_cast<int>(Keys::FIVE):
                    keysPressed[5] = true;
                    break;
                case static_cast<int>(Keys::SIX):
                    keysPressed[6] = true;
                    break;
                case static_cast<int>(Keys::SEVEN):
                    keysPressed[7] = true;
                    break;
                case static_cast<int>(Keys::EIGHT):
                    keysPressed[8] = true;
                    break;
                case static_cast<int>(Keys::NINE):
                    keysPressed[9] = true;
                    break;
                case static_cast<int>(Keys::A):
                    keysPressed[0xA] = true;
                    break;
                case static_cast<int>(Keys::B):
                    keysPressed[0xB] = true;
                    break;
                case static_cast<int>(Keys::C):
                    keysPressed[0xC] = true;
                    break;
                case static_cast<int>(Keys::D):
                    keysPressed[0xD] = true;
                    break;
                case static_cast<int>(Keys::E):
                    keysPressed[0xE] = true;
                    break;
                case static_cast<int>(Keys::F):
                    keysPressed[0xF] = true;
                    break;
                default:
                    break;
                }
            }
        }else if(e.type == SDL_KEYUP){
            switch(e.key.keysym.scancode){
                case static_cast<int>(Keys::ZERO):
                    keysPressed[0] = false;
                    break;
                case static_cast<int>(Keys::ONE):
                    keysPressed[1] = false;
                    break;
                case static_cast<int>(Keys::TWO):
                    keysPressed[2] = false;
                    break;
                case static_cast<int>(Keys::THREE):
                    keysPressed[3] = false;
                    break;
                case static_cast<int>(Keys::FOUR):
                    keysPressed[4] = false;
                    break;
                case static_cast<int>(Keys::FIVE):
                    keysPressed[5] = false;
                    break;
                case static_cast<int>(Keys::SIX):
                    keysPressed[6] = false;
                    break;
                case static_cast<int>(Keys::SEVEN):
                    keysPressed[7] = false;
                    break;
                case static_cast<int>(Keys::EIGHT):
                    keysPressed[8] = false;
                    break;
                case static_cast<int>(Keys::NINE):
                    keysPressed[9] = false;
                    break;
                case static_cast<int>(Keys::A):
                    keysPressed[0xA] = false;
                    break;
                case static_cast<int>(Keys::B):
                    keysPressed[0xB] = false;
                    break;
                case static_cast<int>(Keys::C):
                    keysPressed[0xC] = false;
                    break;
                case static_cast<int>(Keys::D):
                    keysPressed[0xD] = false;
                    break;
                case static_cast<int>(Keys::E):
                    keysPressed[0xE] = false;
                    break;
                case static_cast<int>(Keys::F):
                    keysPressed[0xF] = false;
                    break;
                default:
                    break;
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
    endTime = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    if(diff < 16667){
        std::this_thread::sleep_for(std::chrono::microseconds(1667-diff));
    }
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

bool Display::getKeyPress(int key){
    return keysPressed[key];
}

int Display::getAnyKeyPress(){
    for(int i = 0; i<=0xF; i++){
        if(keysPressed[i]){
            return i;
        }
    }
    return -1;
}