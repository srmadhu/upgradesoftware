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
#include <ClientHandler.hpp>
#include <pthread.h>
   
#define PORT     8080
#define MAXLINE 1024

void verify_class_dlopen();

class UdpClientHandler: public ClientHandler
{
    public:
        void SendRegister();
        void SendMessage(MsgTypeEnum msgType);
        void HandleEvents();

        static UdpClientHandler& Instance(std::string IpAddress, int Port)
        {
            static UdpClientHandler cltHandler(IpAddress, Port);
            return cltHandler;
        }

    private:
        /* No default constructor */
        UdpClientHandler() = delete;
        UdpClientHandler(std::string IpAddress, int Port): m_UdpClt(IpAddress, Port)
        {
            SendRegister();
        }
        UdpClient m_UdpClt;
};
