#pragma once 

#include <iostream>
#include <UdpSocket.hpp>
#include <MsgFormat.hpp>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <cstring>

class UdpClient
{
    public:
        /* Constructor : Stores Ipaddress/Port into member */
        UdpClient(std::string IpAddress, int Port);
        void Send(const void *Buffer, size_t BufLen);
        void Recv(void *Buffer, size_t BufLen, std::string &PeerAddr);
        int GetSocketFd()
        {
            return m_UdpSkt.GetSocketFd();
        }

    private:
        UdpSocket m_UdpSkt;
        struct sockaddr_in m_RemoteAddr;
        socklen_t m_Len;
};

