#include <iostream>
#include <fstream>


#pragma once


class FileReader
{
    public:
        FileReader(std::string &ArgFileName): FileName(ArgFileName)
        {
            ifs = std::ifstream(FileName, std::ios::binary);
        }
        int ReadFile(char *Buffer, int BufSize);
        virtual ~FileReader()
        {
            ifs.close();
        }
    private:
        std::ifstream ifs;
        std::string FileName;
};
