#include <iostream>
#include <sstream>
#include <zipp.hpp>
#include <filesystem>
using namespace ZIPP;

int main()
{
	std::string path = "meme.zip";
	zipp zip;
	const auto& callback = [](std::string filename, uint32_t len) {
		std::cout << "Reading file: " << filename << " " << len << " " << "Bytes" << std::endl;
		}; 
	if (!zip.unZip(path,"meme",callback))
	{
		std::cout << "fail" << std::endl; 
		return -1; 
	}
	return 0;
}