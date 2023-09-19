#include <FileWriter.hpp>


int FileWriter::WriteFile(char *Buffer, int BufSize)
{
    if (ofs.eof())
    {
        std::cout<<"END OF FILE reached."<<std::endl;
        return -1;
    }
    ofs.write(Buffer, BufSize);
    return 0;
}
