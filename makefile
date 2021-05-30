all:
	g++ src/*.cpp -o chip8 -lSDL2 -std=c++17 -Wall -Werror -Wpedantic
