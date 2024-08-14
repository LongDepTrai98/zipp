#include <iostream> 
#include <sstream>
#include <zipp.hpp>
#include <filesystem>
using namespace ZIPP;


int main()
{
	zipp zip; 
	if (!zip.createZip("test.zip", "meme"))
	{
		std::cout << "zipping fail"; 
		return -1; 
	}
	return 0; 
}