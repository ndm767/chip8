#pragma once

#include <SDL2/SDL.h>

class Display{
public:
    Display(bool *r);
    ~Display();

    void startFrame();
    void endFrame();

    void clear();
    int xorAtPos(int x, int y, int val); //returns 1 if any pixels are erased
private:
    int pixels[64][32];
    int scale;

    bool *running;

    SDL_Window *gWindow;
    SDL_Renderer *gRenderer;
};