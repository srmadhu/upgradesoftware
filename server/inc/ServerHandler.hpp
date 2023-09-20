#pragma once
#include <iostream>
#include <UdpSocket.hpp>
#include <UdpServer.hpp>
#include <MsgFormat.hpp>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <cstring>
#include <FileReader.hpp>
#include <iterator>
#include <vector>
#include <sstream>

#define NEWBUFSIZ 1024

class ServerHandler
{
    public:
        ServerHandler() = delete;
        void HandleClientMessage(void *Buffer, size_t BufLen, std::string PeerAddr);
        void HandleCliMessage(std::string cmdLine);
        void HandleEvents();
        static ServerHandler& Instance(int Port)
        {
            static ServerHandler srvHandler(Port);
            return srvHandler;
        }

    private:
        ServerHandler(std::string IpAddress, int Port): udpServ(IpAddress, Port)
        {
            std::cout<<"Listening on "<<IpAddress<<std::endl;
        }
        ServerHandler(int Port): udpServ("", Port)
        {
            std::cout<<"Listen on all ip address "<<std::endl;
        }
       /* Transport is UDP. This can be factory of transport machanisms. */
        UdpServer udpServ;

};
