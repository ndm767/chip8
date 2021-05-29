#include <iostream>
#include <fstream>
#include <sstream>

void loadRom(std::string path, unsigned char* mem){
    std::ifstream f(path, std::ios_base::in | std::ios_base::binary);

    if(!f){
        std::cout<<"Could not open ROM: "<<path<<std::endl;
        std::terminate();
    }

    std::stringstream ss;
    ss << f.rdbuf();
    std::string file = ss.str();

    const char* insStr = file.c_str();
    std::size_t fSize = file.size();
    if(fSize > 0xFFF){
        std::cout<<"Rom "<<path<<" is too big to load into memory! It is "<<fSize<<" bytes!"<<std::endl;
        std::terminate();
    }

    for(int i = 0; i<fSize; i++){
        *(mem + 0x200 + i) = insStr[i];
    }
}

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cout<<"Not enough arguments! Expected file path!"<<std::endl;
        std::terminate();
    }

    std::string romPath(argv[1]);
    std::cout<<romPath<<std::endl;

    unsigned char memory[0xFFF+1];

    loadRom(romPath, &memory[0]);

    return 0;
}