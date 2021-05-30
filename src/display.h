#pragma once

class Display{
public:
    Display();
    ~Display();

    void startFrame();
    void endFrame();

    void clear();
    int xorAtPos(int x, int y, int val); //returns 1 if any pixels are erased
private:
    int pixels[64][32];
    int scale;
};