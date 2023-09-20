#include <FileWriter.hpp>

/*
 * Function : WriteFile
 *     WriteFile writes the passed content if Fd is valid. 
 * Input    : Buffer - Buffer to be written
 *            BugSize - Buffer size
 * Ouput    : Return 0 if success, -1 otherwise.
 *
 */
int FileWriter::WriteFile(const char *Buffer, int BufSize)
{
    if (m_Ofs.bad() || !m_Ofs.is_open())
    {
        std::cerr<<"Writing to "<<m_FileName<<" failed"<<std::endl;
        return -1;
    }
#ifdef DEBUG
    std::cout<<"Writing "<<BufSize<<" into "<<m_FileName<<std::endl;
#endif
    m_Ofs.write(Buffer, BufSize);
    return 0;
}
