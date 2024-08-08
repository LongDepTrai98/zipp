#pragma once
#ifndef _MINI_PP_
#define _MINI_PP_
#include <string>
#include <minizip/zip.h>
#include <minizip/unzip.h>
#include <minizip/ioapi_mem.h>
#include <fstream>
enum class ZIPP_STATUS
{
	ERROR,
	SUCCESS,
	SUCCESS_EOF
};
namespace ZIPP
{
	class zipp
	{
	public:
		zipp();
		~zipp();
	public:
		bool unZip(const std::string& path,
			const std::string& directory);
		bool unZipFromStream(std::istream& stream,
			const std::string& directory); 
		bool unZipFromBuffer(const std::string&,
			const std::string&);
		void release();
	protected:
		std::string getFileName(unzFile,
			bool&);
		bool isDir(unzFile zfile);
		void createFile(const std::string&,
			const std::string&); 
		uint64_t fileSize(unzFile zfile);
		ZIPP_STATUS parseBuffer(unzFile zfile, std::string& buffer);
		ZIPP_STATUS readBuffer(unzFile zfile, std::string& buffer);
		ZIPP_STATUS create(unzFile&,
			const std::string&);
	protected: 
		bool initWithStream(std::istream&);
	protected:
		ourmemory_t m_zipmem;
		zlib_filefunc_def m_filefunc;
		unzFile m_zip; 
	};
}
#endif // !_MINI_PP_

