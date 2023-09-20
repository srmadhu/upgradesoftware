#include <iostream>
#include <UdpSocket.hpp>
#include <UdpClient.hpp>
#include <MsgFormat.hpp>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <cstring>
#include <FileWriter.hpp>
#include <iterator>
#include <vector>
#include <sstream>
#include <string>
#include <unistd.h>
#include <ClientHandler.hpp>

#define BUFSIZE 1024

/* dlopen */
#include <gnu/lib-names.h>
#include <dlfcn.h>
#include <ActionReceiver.hpp>
#include <pthread.h>
   
#define PORT     8080
#define MAXLINE 1024

/* Function : HandleClientMessage
 * Desc     : Handles message from server 
 * Input    : Buffer - message received from server
 *            BufLen - length of the message
 *            PeerAddr - Peer details if any
 * Output   : None
 */
void ClientHandler::HandleClientMessage(void *Buffer, size_t BufLen, std::string PeerAddr)
{
    UpdateMsg_t *msg = (UpdateMsg_t  *) Buffer;
    static int size = 0;

    switch(msg->msgType)
    {
        case MSG_CLREGDONE:
        {
            m_ClientState = CL_STATE_REGDONE;
            break;
        }
        case MSG_SWDLFLNAME:
        {
            std::cout<<"FileName Request Received from "<<PeerAddr<<std::endl;
            msg->Buffer[msg->Length] = '\0';
            m_FileName = msg->Buffer;
#ifdef DEBUG
            std::cout<<"m_FileName is "<<m_FileName<<std::endl;
#endif
            m_FileWriter.OpenFile(m_FileName);
            break;
        }
        case MSG_SWDLFILE:
        {
#ifdef DEBUG
            std::cout<<"SendFile Request Received from "<<PeerAddr<<std::endl;
            std::cout<<"Message buffer length "<<msg->Length<<std::endl;
#endif
            size += msg->Length;
#ifdef DEBUG
            std::cout<<"Total Size = "<<size<<std::endl;
#endif
            m_FileWriter.WriteFile(msg->Buffer, msg->Length);
            break;
        }
        case MSG_SWDLCMPT:
        {
#ifdef DEBUG
            std::cout<<"EndFile Request Received from "<<PeerAddr<<std::endl;
#endif
            m_FileWriter.CloseFile();
            remove("libfunctional.so");
            symlink(m_FileName.c_str(), "libfunctional.so");
            verify_class_dlopen();
        }
    }
}
void ClientHandler::HandleCliMessage(std::string cmdLine)
{
    /* No cmd handling for now */
    return; 
}
