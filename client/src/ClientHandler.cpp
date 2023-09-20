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

void ClientHandler::SendMessage(MsgTypeEnum msgType)
{
    UpdateMsg_t msg;
    msg.msgType = msgType;
    m_UdpClt.Send(&msg, sizeof(msg));
}
void ClientHandler::SendRegister()
{
    /* Assumption is server is already started */
    SendMessage(MSG_CLREGISTER);
    m_ClientState = CL_STATE_REGISTER;
}
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
            std::cout<<"m_FileName is "<<m_FileName<<std::endl;
            m_FileWriter.SetFileName(m_FileName);
            break;
        }
        case MSG_SWDLFILE:
        {
            std::cout<<"SendFile Request Received from "<<PeerAddr<<std::endl;
            std::cout<<"Message buffer length "<<msg->Length<<std::endl;
            size += msg->Length;
            std::cout<<"Total Size = "<<size<<std::endl;
            m_FileWriter.WriteFile(msg->Buffer, msg->Length);
            break;
        }
        case MSG_SWDLCMPT:
        {
            std::cout<<"EndFile Request Received from "<<PeerAddr<<std::endl;
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
void ClientHandler::HandleEvents()
{

    for(;;)
    {
        int ready = 0, maxFd = 0;
        int udpFd = m_UdpClt.GetSocketFd();
        struct timeval tv;
        fd_set readFdSet;
        maxfd = std::max(udpFd, 0) + 1;


        /* Handle both server messages and user input */
        FD_ZERO(&readFdSet);
        FD_SET(udpFd, &readFdSet);
        FD_SET(fileno(stdin), &readFdSet);
        tv.tv_sec = 10; tv.tv_usec = 0;
        std::cout<<std::endl<<"NxtClient# ";
        std::cout.flush();
        ready = select(maxfd, &readFdSet, NULL, NULL, &tv);

        /* Irrespective of timeout of events, attempt register */
        if (m_ClientState == CL_STATE_REGISTER)
        {
            SendRegister();
        }
        /* if select returned error, still continue */
        if (ready < 0)
        {
            std::cout<<"Select return socket error : "<<errno<<std::endl;
            continue;
        } 
                
        if (FD_ISSET(udpFd, &readFdSet))
        {
            UpdateMsg_t  msg;
            size_t Len = sizeof(msg);
            std::string PeerAddr;
            m_UdpClt.Recv(&msg, Len, PeerAddr);
            HandleClientMessage(&msg, Len, PeerAddr);
        }
        else if (FD_ISSET(fileno(stdin), &readFdSet))
        {
            std::string cmdInput;
            std::getline(std::cin, cmdInput);
            if ( cmdInput  == "show version")
            {
                verify_class_dlopen();
            }
            else if ( cmdInput == "exit")
            {
                return;
            }
        }
    }
    return;
}
