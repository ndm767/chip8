# Chip8

A Chip8 Emulator written in C++ with SDL2  

Based upon [Cowgod's Chip-8 Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)  

## How to use

`./chip8 [path-to-rom]`  
A good source of roms is [dmatlack/chip8/roms](https://github.com/dmatlack/chip8/tree/master/roms)  

### Key layout

    1 2 3 4          1 2 3 C  
    q w e r -------> 4 5 6 D  
    a s d f -------> 7 8 9 E  
    z x c v          A 0 B F  
Escape closes the emulator  

## Yet to be done

- sound
- lock to 60hz
- custom screen size
