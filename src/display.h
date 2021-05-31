#pragma once

#include <SDL2/SDL.h>

enum class Keys{    
    ZERO = SDL_SCANCODE_0,
    ONE = SDL_SCANCODE_1,
    TWO = SDL_SCANCODE_2,
    THREE = SDL_SCANCODE_3,
    FOUR = SDL_SCANCODE_4,
    FIVE = SDL_SCANCODE_5,
    SIX = SDL_SCANCODE_6,
    SEVEN = SDL_SCANCODE_7,
    EIGHT = SDL_SCANCODE_8,
    NINE = SDL_SCANCODE_9,
    A = SDL_SCANCODE_A,
    B = SDL_SCANCODE_B,
    C = SDL_SCANCODE_C,
    D = SDL_SCANCODE_D,
    E = SDL_SCANCODE_E,
    F = SDL_SCANCODE_F
};

class Display{
public:
    Display(bool *r);
    ~Display();

    void startFrame();
    void endFrame();

    void clear();
    int xorAtPos(int x, int y, int val); //returns 1 if any pixels are erased
    bool getKeyPress(int key);
    int getAnyKeyPress();
private:
    int pixels[64][32];
    int scale;

    bool *running;

    bool keysPressed[0xF+1];

    SDL_Window *gWindow;
    SDL_Renderer *gRenderer;
};