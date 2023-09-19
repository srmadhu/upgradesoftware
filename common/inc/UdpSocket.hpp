/******************************************************************************
    FileName: UdpSocket.hpp
    
    UdpSocket handles socket level operations for udp protocol 

    Yet to support IPv6 implementation
******************************************************************************/
#pragma once 


#include <iostream>
#include <string>
#include <sys/socket.h>


class UdpSocket
{
    public:
        UdpSocket(): sockFd(-1)
        { 
            std::cout<<"UdpSocket:: Constructor called "<<std::endl;
            CreateSocket(); 
        }

        int  CreateSocket();

        int  BindSocket(std::string IpAddress, int Port);

        int  SendTo(const void* Buffer, const size_t BufLen, std::string RemoteAddr, int Port);

        int  SendTo(const void* Buffer, const size_t BufLen, struct sockaddr_in &RemoteAddr, socklen_t Len);

        int  RecvFrom(void* Buffer, size_t BufferSize, struct sockaddr_in &RemoteAddr, socklen_t &RemoteAddrLen);

        int  GetSocketFd()
        {
            return sockFd;
        }

    private:
        int sockFd = -1;
};
