#pragma once 
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
#include <MsgFormat.hpp>

#define BUFSIZE 1024

/* dlopen */
#include <gnu/lib-names.h>
#include <dlfcn.h>
#include <ActionReceiver.hpp>
#include <pthread.h>
   
#define PORT     8080
#define MAXLINE 1024

void verify_class_dlopen();

class ClientHandler
{
    public:
        /* No default constructor */
        ClientHandler() = delete;
        ClientHandler(std::string IpAddress, int Port): m_UdpClt(IpAddress, Port)
        {
            m_ClientState = STATE_INIT;
            SendRegister();
            verify_class_dlopen();
        }
        void SendRegister();
        void SendMessage(MsgTypeEnum msgType);
        void HandleClientMessage(void *Buffer, size_t BufLen, std::string PeerAddr);
        void HandleCliMessage(std::string cmdLine);

        void HandleEvents();

    private:
        FileWriter m_FileWriter;
        std::string m_FileName = "";
        StateEnum m_ClientState;
        UdpClient m_UdpClt;

};
