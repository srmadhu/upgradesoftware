#include <iostream>
#include <fstream>


#pragma once


class FileReader
{
    public:
        /* Default constructor - call synthesized constructor */
        FileReader() = default;
        /* Initialize FileReader with Filename and open it */
        FileReader(std::string &FileName)
        {
            OpenFile(FileName);
        }
        /* Function : OpenFile
         * Desc     : Set member to proper file name and open/store Fd 
         * Input    : FileName - Name of the file to be read
         * Output   : 0 if success, -1 otherwise.
         */
        int OpenFile(const std::string FileName)
        {
            m_FileName = FileName;
#if DEBUG            
            std::cout<<"FileReader:: Opening File "<<m_FileName<<std::endl;
#endif
            m_Ifs.open(m_FileName, std::ofstream::binary);
            if (!m_Ifs.is_open())
            {
                std::cerr<<"File "<<m_FileName<<" failed while opening "<<std::endl;
                return -1;
            }
            return 0;
        }
        /*
         * Function : ReadFile
         * Desc     : ReadFile reads the content in to buffer if Fd is valid. 
         * Input    : Buffer - Buffer to store contents
         *            BugSize - Buffer size
         * Ouput    : Return 0 if success, -1 otherwise.
         *
         */
        int ReadFile(char *Buffer, int BufSize);
        /* Function : CloseFile
         * Desc     : Close the file descriptor
         * Input    : None
         * Output   : None
         */
        void CloseFile()
        {
#if DEBUG            
            std::cout<<"FileReader:: Closing File "<<m_FileName<<std::endl;
#endif
            m_Ifs.close();
        }
        /* Function : FileExists
         * Desc     : File is present or not 
         * Input    : None
         * Output   : None
         */
        bool FileExists()
        {
            return m_Ifs.is_open();
        }
        /* Virtual Destuctor */
        virtual ~FileReader()
        {
            CloseFile();
        }
    private:
        /* Input File Stream */
        std::ifstream m_Ifs;
        /* File Name */
        std::string m_FileName;
};
