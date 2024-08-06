#include "minipp.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

#define BUF_SIZE 8192
#define MAX_NAMELEN 256

minipp::minipp(const std::string& path) : m_Zipfile(path)
{

}

bool minipp::unZip(const std::string& directory)
{
    std::filesystem::create_directories(directory);
    std::string filename; 
    unzFile uzfile;
    bool isUtf8{ false }; 
    uzfile = unzOpen64(m_Zipfile.c_str());
    uint64_t len;
    MINIPP_RESULT mini_result = MINIPP_RESULT::SUCCESS; 
    if (uzfile == nullptr)
        throw std::exception("Couldn't open zip file"); 
    do {

        filename = getFileName(uzfile, isUtf8);
        if (filename.empty()) continue; 
        std::string folder;
        directory.empty() ? folder = directory + filename : folder = directory + "/" + filename;
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
        mini_result = read_Buf(uzfile, buffer); 
        createFile(folder, buffer); 
        if (mini_result == MINIPP_RESULT::ERROR) {
            break; 
        }

    } while (mini_result == MINIPP_RESULT::SUCCESS); 
    if (mini_result == MINIPP_RESULT::ERROR) {
        throw std::exception("failed to read zip"); 
        return false;
    }
    unzClose(uzfile);
    return true;
}

std::string minipp::getFileName(unzFile zfile, bool& isutf8)
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

bool minipp::isDir(unzFile zfile)
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

uint64_t minipp::fileSize(unzFile zfile)
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

MINIPP_RESULT minipp::readBuffer(unzFile zfile, std::string& buffer)
{
    unsigned char tbuf[BUF_SIZE];
    int           red;
    int           ret;
    if (zfile == NULL)
        return MINIPP_RESULT::ERROR;
    ret = unzOpenCurrentFile(zfile);
    if (ret != UNZ_OK)
        return MINIPP_RESULT::ERROR;
    while ((red = unzReadCurrentFile(zfile, tbuf, sizeof(tbuf))) > 0) {
        buffer += std::string((const char*)(tbuf), red);
    }
    if (red < 0) {
        unzCloseCurrentFile(zfile);
        return MINIPP_RESULT::ERROR;
    }
    unzCloseCurrentFile(zfile);
    if (unzGoToNextFile(zfile) != UNZ_OK)
        return MINIPP_RESULT::SUCCESS_EOF;
    return MINIPP_RESULT::SUCCESS;
}

MINIPP_RESULT minipp::read_Buf(unzFile zfile, std::string& buffer)
{
    MINIPP_RESULT result = readBuffer(zfile, buffer); 
    return result;
}

void minipp::createFile(const std::string& file,
    const std::string& buffer)
{
    std::ofstream f(file, std::ofstream::binary | std::ofstream::out);
    f << buffer;
    f.close();
}
