#include <iostream> 
#include <sstream>
#include <zipp.hpp>
#include <filesystem>
using namespace ZIPP;


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