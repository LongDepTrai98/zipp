#include <iostream> 
#include <sstream>
#include <zipp.hpp>
#include <filesystem>
#include <functional>
using namespace ZIPP; 

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