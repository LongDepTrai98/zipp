#pragma once
#ifndef _MINI_PP_
#define _MINI_PP_
#include <string>
#include <minizip/zip.h>
#include <minizip/unzip.h>
enum class MINIPP_RESULT
{
	ERROR,
	SUCCESS,
	SUCCESS_EOF
};
class minipp
{
public:
	minipp(const std::string&);
public: 
	bool unZip(const std::string&);
protected: 
	std::string getFileName(unzFile,
		bool&);
	bool isDir(unzFile zfile);
	uint64_t fileSize(unzFile zfile);
	MINIPP_RESULT readBuffer(unzFile zfile, std::string& buffer); 
	MINIPP_RESULT read_Buf(unzFile zfile, std::string& buffer);
	void createFile(const std::string&,
		const std::string&); 
protected: 
	std::string m_Zipfile{};
};
#endif // !_MINI_PP_

