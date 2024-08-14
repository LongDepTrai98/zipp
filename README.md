# zipp
a simple project C++ wrapper around minizip compression library
## feature 
* Decompression from zip file
* Decompression from memory
* Create zip from folder
## Build
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
*unzip.cpp
``` C++
int main()
{
  //Decompression from file 
  std::string path = "meme.zip";
  zipp zip; 
  if (!zip.unZip(path, "unzip"))
  {
    std::cout << "failed"; 
  }
  //Decompression from memory 
  std::string buffer = ReadFile(path); 
  if (!zip.unZipFromBuffer(buffer, "buffer"))
  {
    std::cout << "failed"; 
  }
  return 0; 
}
```
*zipp.cpp
``` C++
int main()
{
	zipp zip;
  //create zip from folder
	if (!zip.createZip("test.zip", "meme"))
	{
		std::cout << "zipping fail"; 
		return -1; 
	}
	return 0; 
}
```
