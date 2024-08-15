#pragma once
#ifndef _MINI_PP_
#define _MINI_PP_
#include <string>
#include <minizip/zip.h>
#include <minizip/unzip.h>
#include <minizip/ioapi_mem.h>
#include <fstream>
#include <filesystem>
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
	using PATH = std::filesystem::path; 
	class zipp
	{
	public:
		zipp();
		~zipp();
	public:
		bool unZip(const PATH& path,
			const PATH& directory,
			CALLBACK callback = nullptr);
		bool unZipFromStream(std::istream& stream,
			const PATH& directory, 
			CALLBACK callback = nullptr); 
		bool unZipFromBuffer(const std::string&,
			const PATH&, 
			CALLBACK callback = nullptr);
		bool createZip(const PATH&, 
			PATH folder,
			CALLBACK callback = nullptr);
		void release();
	protected:
		//unzip
		std::string getFileName(unzFile,
			bool&);
		uint64_t fileSize(unzFile zfile);
		ZIPP_STATUS parseBuffer(unzFile zfile, 
			std::string& buffer);
		ZIPP_STATUS readBuffer(unzFile zfile,
			std::string& buffer);
		ZIPP_STATUS create(unzFile&,
			const PATH&,
			CALLBACK callback);
		//create zip
		bool zip_add_dir(zipFile zfile, 
			const char* dirname);
		bool zip_add_buf(zipFile zfile, 
			const char* zfilename, 
			const unsigned char* buf, 
			uint32_t buflen);
		bool initWithStream(std::istream&);
		bool isDir(unzFile zfile);
		void zip_read_buf(const PATH& filename,
			std::string& buffer);
		void readBuffFromFile(const PATH&,
			const PATH&,
			CALLBACK&
		);
		void createFile(const PATH&,
			const std::string&);
	protected:
		ourmemory_t m_zipmem;
		zlib_filefunc_def m_filefunc;
		zipFile m_zip;
		ZIPP_STATE m_zipp_state; 
	};
}
#endif // !_MINI_PP_

