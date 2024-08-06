

#include <iostream>
#include "minipp.hpp"
int main()
{
    std::string path = "meme.zip";
    minipp unzip(path); 
    unzip.unZip("test"); 
}

