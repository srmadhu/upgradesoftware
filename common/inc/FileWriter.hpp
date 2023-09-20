#include <iostream>
#include <fstream>


#pragma once


class FileWriter
{
    public:
        /* Default constructor - call synthesized constructor */
        FileWriter()= default;
        /* Initialize FileWrite with FileName and open it */
        FileWriter(const std::string &FileName)
        {
            OpenFile(FileName);
        }
        /* Function : OpenFile
         * Desc     : Set member to proper file name and open/store Fd 
         * Input    : FileName - Name of the file to be written
         * Output   : 0 if success, -1 otherwise.
         */
        int OpenFile(const std::string FileName)
        {
            m_FileName = FileName;
#ifdef DEBUG            
            std::cout<<"FileWriter:: Opening File "<<m_FileName<<std::endl;
#endif
            m_Ofs.open(m_FileName, std::ofstream::out | std::ofstream::app);
            if (!m_Ofs.is_open())
            {
                std::cerr<<"File "<<m_FileName<<" failed while opening "<<std::endl;
                return -1;
            }
            return 0;
        }
        /*
         * Function : WriteFile
         * Desc     : WriteFile writes the passed content if Fd is valid. 
         * Input    : Buffer - Buffer to be written
         *            BugSize - Buffer size
         * Ouput    : Return 0 if success, -1 otherwise.
         *
         */
        int WriteFile(const char *Buffer, int BufSize);
        /* Function : CloseFile
         * Desc     : Close the file descriptor
         * Input    : None
         * Output   : None
         */
        void CloseFile()
        {
#ifdef DEBUG            
            std::cout<<"FileWriter:: Closing File "<<m_FileName<<std::endl;
#endif
            m_Ofs.close();
        }
        /* Virtual Destructor */
        virtual ~FileWriter()
        {
           CloseFile();
        }
    private:
        /* Output File Stream */
        std::ofstream m_Ofs;
        /* File Name */
        std::string m_FileName;
};
