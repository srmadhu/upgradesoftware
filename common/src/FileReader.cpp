#include <FileReader.hpp>

/*
 * Function : ReadFile
 * Desc     : ReadFile reads the content in to buffer if Fd is valid. 
 * Input    : Buffer - Buffer to store contents
 *            BugSize - Buffer size
 * Ouput    : Return 0 if success, -1 otherwise.
 *
 */
int FileReader::ReadFile(char *Buffer, int BufSize)
{
    if (m_Ifs.eof() || m_Ifs.bad())
    {
        std::cout<<"END OF FILE reached."<<std::endl;
        return -1;
    }
    m_Ifs.read(Buffer, BufSize);
    int number = m_Ifs.gcount();
 #ifdef DEBUG
    std::cout<<"Read "<<number<<" bytes from "<<m_FileName<<std::endl;
 #endif
    return number;
}
