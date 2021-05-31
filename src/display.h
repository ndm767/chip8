#pragma once

#include <SDL2/SDL.h>

enum class Keys{    
    ZERO = SDL_SCANCODE_X,
    ONE = SDL_SCANCODE_1,
    TWO = SDL_SCANCODE_2,
    THREE = SDL_SCANCODE_3,
    FOUR = SDL_SCANCODE_Q,
    FIVE = SDL_SCANCODE_W,
    SIX = SDL_SCANCODE_E,
    SEVEN = SDL_SCANCODE_A,
    EIGHT = SDL_SCANCODE_S,
    NINE = SDL_SCANCODE_D,
    A = SDL_SCANCODE_Z,
    B = SDL_SCANCODE_C,
    C = SDL_SCANCODE_4,
    D = SDL_SCANCODE_R,
    E = SDL_SCANCODE_F,
    F = SDL_SCANCODE_V
};

class Display{
public:
    Display(bool *r, int s);
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