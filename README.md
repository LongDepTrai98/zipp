# zipp
a simple project C++ wrapper around minizip compression library
## Feature 
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
* unzip.cpp
``` C++
int main()
{
	std::string path = "meme.zip";
	zipp zip;
	const auto& callback = [](std::string filename, uint64_t len) {
		std::cout << "Reading file: " << filename << " " << len << " " << "Bytes" << std::endl;
		};
	if (!zip.unZip(path, 
		"testunzip",
		callback))
	{
		std::cout << "failed";
	}
	return 0; 
}
```
* zipp.cpp
``` C++
int main()
{
	zipp zip; 
	auto callback = [](std::string filename, uint32_t len) {
		std::cout << "Reading file: " << filename << " " << len << " " << "Bytes" << std::endl;
		}; 
	if (!zip.createZip("testzip.zip",
		"meme",
		callback))
	{
		std::cout << "zipping fail"; 
		return -1; 
	}
	return 0; 
}
```
