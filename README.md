# zipp
a simple project C++ wrapper around minizip compression library
## feature 
* decompression from zip file
* decompression from memory
## building
```
  git clone https://github.com/LongDepTrai98/zipp.git
  cd zipp
  mkdir build
  cd build
  cmake ../
```
## Usage
* Header
```
#include <zipp.hpp>
using namespace ZIPP; 
```
* main.cpp
```
int main()
{
  //file 
  std::string path = "meme.zip";
  zipp zip; 
  if (!zip.unZip(path, "unzip"))
  {
    std::cout << "failed"; 
  }
  //memory 
  std::string buffer = ReadFile(path); 
  if (!zip.unZipFromBuffer(buffer, "buffer"))
  {
    std::cout << "failed"; 
  }
  return 0; 
}
```
