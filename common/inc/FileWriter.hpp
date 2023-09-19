#include <iostream>
#include <fstream>


#pragma once


class FileWriter
{
    public:
        FileWriter()= default;
        FileWriter(std::string &ArgFileName): FileName(ArgFileName)
        {
            SetFileName(FileName);
        }
        void SetFileName(std::string ArgFileName)
        {
            FileName = ArgFileName;
            ofs.open(FileName, std::ofstream::out | std::ofstream::app);
        }
        void CloseFile()
        {
            ofs.close();
        }
        int WriteFile(char *Buffer, int BufSize);
        virtual ~FileWriter()
        {
            ofs.close();
        }
    private:
        std::ofstream ofs;
        std::string FileName;
};
