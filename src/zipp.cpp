#include "zipp.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#define BUF_SIZE 8192
#define MAX_NAMELEN 256
namespace ZIPP
{
    zipp::zipp()
    {
        m_zipmem.base = NULL; 
        m_zip = NULL; 
    }

    zipp::~zipp()
    {
        release(); 
    }

    bool zipp::unZip(const std::string& path,
        const std::string& directory)
    {
        m_zip = unzOpen64(path.c_str());
        const auto& mini_result = create(m_zip, 
            directory); 
        if (mini_result == ZIPP_STATUS::ERROR) {
            throw std::exception("failed to read zip");
            return false;
        }
        release(); 
        return true;
    }

    bool zipp::unZipFromStream(std::istream& buffer,
        const std::string& directory)
    {
        //init stream 
        if (!initWithStream(buffer)) return false; 
        bool isCreate =  create(m_zip, directory) == ZIPP_STATUS::SUCCESS || create(m_zip, directory) == ZIPP_STATUS::SUCCESS_EOF;
        release(); 
        return isCreate; 
    }

    bool zipp::unZipFromBuffer(const std::string& buffer,
        const std::string& directory)
    {
        std::istringstream iss(buffer);
        const size_t& size = buffer.length(); 
        if (!initWithStream(iss)) return false; 
        bool isCreate = create(m_zip, directory) == ZIPP_STATUS::SUCCESS || create(m_zip, directory) == ZIPP_STATUS::SUCCESS_EOF;
        release(); 
        return isCreate; 
    }

    void zipp::release()
    {
        if (m_zip != NULL)
        {
            unzClose(m_zip);
            m_zip = NULL;
        }

        if (m_zipmem.base != NULL)
        {
            free(m_zipmem.base);
            m_zipmem.base = NULL;
        }
    }

    std::string zipp::getFileName(unzFile zfile, bool& isutf8)
    {
        std::string filename{ "" };
        char            name[MAX_NAMELEN];
        unz_file_info64 finfo;
        int             ret;

        if (zfile == NULL)
            filename;

        ret = unzGetCurrentFileInfo64(zfile, &finfo, name, sizeof(name), NULL, 0, NULL, 0);
        if (ret != UNZ_OK) return filename;
        isutf8 = (finfo.flag & (1 << 11)) ? true : false;
        filename = std::string(name);
        return filename;
    }

    bool zipp::isDir(unzFile zfile)
    {
        char            name[MAX_NAMELEN];
        unz_file_info64 finfo;
        size_t          len;
        int             ret;

        if (zfile == NULL)
            return false;

        ret = unzGetCurrentFileInfo64(zfile, &finfo, name, sizeof(name), NULL, 0, NULL, 0);
        if (ret != UNZ_OK)
            return false;

        len = strlen(name);
        if (finfo.uncompressed_size == 0 && len > 0 && name[len - 1] == '/')
            return true;
        return false;
    }

    uint64_t zipp::fileSize(unzFile zfile)
    {
        unz_file_info64 finfo;
        int             ret;

        if (zfile == NULL)
            return 0;

        ret = unzGetCurrentFileInfo64(zfile, &finfo, NULL, 0, NULL, 0, NULL, 0);
        if (ret != UNZ_OK)
            return 0;
        return finfo.uncompressed_size;
    }

    ZIPP_STATUS zipp::parseBuffer(unzFile zfile, std::string& buffer)
    {
        unsigned char tbuf[BUF_SIZE];
        int           red;
        int           ret;
        if (zfile == NULL)
            return ZIPP_STATUS::ERROR;
        ret = unzOpenCurrentFile(zfile);
        if (ret != UNZ_OK)
            return ZIPP_STATUS::ERROR;
        while ((red = unzReadCurrentFile(zfile, tbuf, sizeof(tbuf))) > 0) {
            buffer += std::string((const char*)(tbuf), red);
        }
        if (red < 0) {
            unzCloseCurrentFile(zfile);
            return ZIPP_STATUS::ERROR;
        }
        unzCloseCurrentFile(zfile);
        if (unzGoToNextFile(zfile) != UNZ_OK)
            return ZIPP_STATUS::SUCCESS_EOF;
        return ZIPP_STATUS::SUCCESS;
    }

    ZIPP_STATUS zipp::readBuffer(unzFile zfile, std::string& buffer)
    {
        ZIPP_STATUS result = parseBuffer(zfile, buffer);
        return result;
    }

    void zipp::createFile(const std::string& file,
        const std::string& buffer)
    {
        std::ofstream f(file, std::ofstream::binary | std::ofstream::out);
        f << buffer;
        f.close();
    }

    bool zipp::initWithStream(std::istream& stream)
    {
        stream.seekg(0, std::ios::end);
        std::streampos s = stream.tellg();
        if (s < 0)
        {
            return NULL;
        }
        size_t size = static_cast<size_t>(s);
        stream.seekg(0);

        if (size > 0u)
        {
            m_zipmem.base = new char[size];
            m_zipmem.size = static_cast<uLong>(size);
            stream.read(m_zipmem.base, std::streamsize(size));
        }
        fill_memory_filefunc(&m_filefunc, &m_zipmem);
        m_zip =  unzOpen2("__notused__", &m_filefunc);
    }

    ZIPP_STATUS zipp::create(unzFile& uzfile,
        const std::string& directory)
    {
        bool isUtf8{ false };
        uint64_t len;
        ZIPP_STATUS mini_result = ZIPP_STATUS::SUCCESS;
        std::string filename;
        std::string tmp_directory; 
        directory.empty() ? tmp_directory = directory : tmp_directory = directory + "/"; 
        std::filesystem::create_directories(directory); 
        if (uzfile == nullptr)
            throw std::exception("Couldn't open zip file");

        do {

            filename = getFileName(uzfile, isUtf8);
            if (filename.empty()) continue;
            std::string folder;
            folder = tmp_directory + filename; 
            if (isDir(uzfile))
            {
                try
                {
                    std::filesystem::create_directories(folder);
                    unzGoToNextFile(uzfile);
                    continue;
                }
                catch (const std::exception& e)
                {
                    std::cout << e.what();
                }
            }
            len = fileSize(uzfile);
            std::string buffer;
            mini_result = readBuffer(uzfile, buffer);
            createFile(folder, buffer);
            if (mini_result == ZIPP_STATUS::ERROR) {
                break;
            }

        } while (mini_result == ZIPP_STATUS::SUCCESS);

        return mini_result;
    }; 
}