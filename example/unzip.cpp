#include <iostream> 
#include <sstream>
#include <zipp.hpp>
#include <filesystem>
#include <functional>
using namespace ZIPP; 

static std::string ReadFile(const std::string& filename) {
	if (filename.empty() || (filename.size() == 1 && filename[0] == '-')) {
		return std::string{ std::istreambuf_iterator<char>(std::cin.rdbuf()),
						   std::istreambuf_iterator<char>() };
	}
	std::ifstream stream{ filename, std::ios::in | std::ios::binary };
	if (!stream) {
		return {};
	}
	stream.exceptions(std::ifstream::failbit);
	std::string buffer{ std::istreambuf_iterator<char>(stream.rdbuf()),
					   std::istreambuf_iterator<char>() };
	stream.close();
	return buffer;
}
int main()
{
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
	//create zip
	return 0; 
}