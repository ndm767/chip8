#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cout<<"Not enough arguments! Expected file path!"<<std::endl;
        std::terminate();
    }

    std::string romPath(argv[1]);
    std::cout<<romPath<<std::endl;

    unsigned char memory[0xFFF+1];
    
    return 0;
}