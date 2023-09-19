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

void ClientHandler:SendMessage(MsgTypeEnum msgType)
{
    UpdateMsg_t msg;
    msg.msgType = msgType;
    m_udpClt.Send(&msg, sizeof(msg));
}
void ClientHandler::SendRegister()
{
    /* Assumption is server is already started */
    SendMessage(MSG_REGISTER);
    m_ClientState = STATE_REGISTER;
}
void ClientHandler::HandleClientMessage(void *Buffer, size_t BufLen, std::string PeerAddr)
{
    UpdateMsg_t *msg = (UpdateMsg_t  *) Buffer;
    static int size = 0;

    switch(msg->msgType)
    {
        case MSG_REGDONE:
        {
            m_ClientState = STATE_REGDONE;
            break;
        }
        case MSG_FILENAME:
        {
            std::cout<<"FileName Request Received from "<<PeerAddr<<std::endl;
            msg->Buffer[msg->Length] = '\0';
            m_FileName = msg->Buffer;
            std::cout<<"m_FileName is "<<m_FileName<<std::endl;
            m_FileWriter.SetFileName(m_FileName);
            break;
        }
        case MSG_SENDFILE:
        {
            std::cout<<"SendFile Request Received from "<<PeerAddr<<std::endl;
            std::cout<<"Message buffer length "<<msg->Length<<std::endl;
            std::cout<<"Message counter "<<msg->counter<<std::endl;
            size += msg->Length;
            std::cout<<"Total Size = "<<size<<std::endl;
            m_FileWriter.WriteFile(msg->Buffer, msg->Length);
            break;
        }
        case MSG_FILEEND:
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
    std::stringstream ss(cmdLine);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> cmd(begin, end);
    int bytesRead = -1;
    if (cmd[0] == PUSH_COMMAND)
    {
        // Print Version
    }
    return; 
}
void ClientHandler::HandleEvents()
{
    fd_set readFdSet;
    int maxfd = 0;
    FD_ZERO(&readFdSet);

    int udpFd = m_UdpClt.GetSocketFd();
            
    maxfd = std::max(udpFd, 0) + 1;
            
    while (1)
    {
        int ready = 0, Len = 0;
        struct timeval tv;
        FD_SET(udpFd, &readFdSet);
        FD_SET(fileno(stdin), &readFdSet);
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        std::cout<<std::endl<<"NxtClient# ";
        std::cout.flush();
        ready = select(maxfd, &readFdSet, NULL, NULL, &tv);
                
        if (FD_ISSET(udpFd, &readFdSet))
        {
            UpdateMsg_t  msg;
            size_t Len = sizeof(msg);
            std::string PeerAddr;
            std::cout<<"udp fd is set "<<std::endl;
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
        else
        {
            if ( m_ClientState == STATE_REGISTER)
            {
                       SendRegister();
            }
        }
    }
    return;
}
