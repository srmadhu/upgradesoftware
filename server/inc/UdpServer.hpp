#pragma once 
#include <iostream>
#include <UdpSocket.hpp>
#include <MsgFormat.hpp>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <cstring>


#define BUFSIZE 1024

class UdpServer
{
    public:
        UdpServer(std::string IpAddress, int Port);
        UdpServer(int Port);
        void Send(const void *Buffer, size_t BufLen);
        void Recv(void *Buffer, size_t BufLen, std::string &PeerAddr);
        int GetSocketFd()
        {
           return udpSkt.GetSocketFd();
        }
    private:
       UdpSocket udpSkt; 
       struct  sockaddr_in RemoteAddr;
       socklen_t Len;
};
