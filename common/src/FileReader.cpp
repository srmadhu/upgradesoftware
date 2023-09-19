#include <FileReader.hpp>


int FileReader::ReadFile(char *Buffer, int BufSize)
{
    if (ifs.eof())
    {
        std::cout<<"END OF FILE reached."<<std::endl;
        return -1;
    }
    ifs.read(Buffer, BufSize);
    int number = ifs.gcount();
    return number;
}
