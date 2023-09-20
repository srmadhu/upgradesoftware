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

class UdpClientHandler: public ClientHandler
{
    public:
        /* Function : SendMessage
         * Desc     : Send buffer with Len to Udp peer
         * Input    : Buffer - Message to be sent
         * Len      : Size of message 
         */
        void SendMessage(void *Buffer, size_t Len)
        {
 #ifdef DEBUG
            std::cout<<"Sending Message from UdpClientHandler"<<std::endl;
 #endif
            m_UdpClt.Send(Buffer, Len);
        }
        /* Function : RecvMessage
         * Desc     : Recv message from remote peer. Handles
         *              action handling for the message.
         * Input    : None
         * Len      : None
         */
        void RecvMessage();

        /* Function : Instance
         * Desc     : Creating UdpClientHandler instance
         * Input    : IpAddress - Remote Ip Address
         *            Port      - Remote Port
         * Output   : UdpClientHandler instance 
         */
        static UdpClientHandler& Instance(std::string IpAddress, int Port)
        {
            static UdpClientHandler cltHandler(IpAddress, Port);
            return cltHandler;
        }

    protected:
        /* No default constructor */
        UdpClientHandler() = delete;
        /* UdpClientHandler constructor */
        UdpClientHandler(std::string IpAddress, int Port): m_UdpClt(IpAddress, Port)
        {
 #ifdef DEBUG
            std::cout<<"UdpClientHandler:: constructor is called "<<std::endl;
 #endif
        }
    private:
        /* UdpClient object */
        UdpClient m_UdpClt;
};
