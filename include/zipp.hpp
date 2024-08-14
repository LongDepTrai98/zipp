#pragma once
#ifndef _MINI_PP_
#define _MINI_PP_
#include <string>
#include <minizip/zip.h>
#include <minizip/unzip.h>
#include <minizip/ioapi_mem.h>
#include <fstream>
#include <functional>


#ifndef ERROR
#undef ERROR
#endif // !ERROR




enum class ZIPP_STATUS
{
	ERROR,
	SUCCESS,
	SUCCESS_EOF
};

enum class ZIPP_STATE
{
	CREATE,
	UNZIP
};

namespace ZIPP
{
	using CALLBACK = std::function<void(std::string,uint64_t)>; 
	class zipp
	{
	public:
		zipp();
		~zipp();
	public:
		bool unZip(const std::string& path,
			const std::string& directory,
			CALLBACK callback = nullptr);
		bool unZipFromStream(std::istream& stream,
			const std::string& directory, 
			CALLBACK callback = nullptr); 
		bool unZipFromBuffer(const std::string&,
			const std::string&, 
			CALLBACK callback = nullptr);
		bool createZip(const std::string&, 
			std::string folder);
		void release();
	protected:
		//unzip
		std::string getFileName(unzFile,
			bool&);
		bool isDir(unzFile zfile);
		void createFile(const std::string&,
			const std::string&); 
		uint64_t fileSize(unzFile zfile);
		ZIPP_STATUS parseBuffer(unzFile zfile, 
			std::string& buffer);
		ZIPP_STATUS readBuffer(unzFile zfile,
			std::string& buffer);
		ZIPP_STATUS create(unzFile&,
			const std::string&,
			CALLBACK callback);
		//create zip
		bool zip_add_dir(zipFile zfile, 
			const char* dirname);
		bool zip_read_buf(const std::string& filename, 
			std::string& buffer);
		bool zip_add_buf(zipFile zfile, const char* zfilename, 
			const unsigned char* buf, 
			uint32_t buflen);
		bool initWithStream(std::istream&);
	protected:
		ourmemory_t m_zipmem;
		zlib_filefunc_def m_filefunc;
		zipFile m_zip;
		ZIPP_STATE m_zipp_state; 
	};
}
#endif // !_MINI_PP_

