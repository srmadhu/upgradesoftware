/******************************************************************************
    FileName: UdpSocket.hpp
    
    UdpSocket handles socket level operations for udp protocol 

    Yet to support IPv6 implementation
******************************************************************************/
#pragma once 


#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

class UdpSocket
{
    public:
        /* Default constructor : Create Socket */
        UdpSocket()
        { 
#ifdef DEBUG
            std::cout<<"UdpSocket:: Constructor called "<<std::endl;
#endif
            CreateSocket(); 
        }
        /* 
         * Function : CreateSocket
         * Desc     : Create Udp Socket for Server or Client 
         * Input    : None
         * Output   : Socket Descriptor if successful, -1 otherwise
         */
        int  CreateSocket();

        /* 
         * Function : BindSocket
         * Desc     : Binding Socket to specific IP and Port. Mostly
         *      called from server but applicable to client also.
         * Input    : IpAddress - Local IpAddress to bind
         *            Port - Port to bind
         * Output   : Socket Descriptor if successful, -1 otherwise
         */
        int  BindSocket(const std::string IpAddress, int Port);

        /*
         * Function : SendTo
         * Desc     : Send Buffer with size BufLen to RemoteAddr:Port
         * Input    : Buffer - bytes to be sent
         *            BugLen - Length of bytes to be sent
         *            RemoteAddr - Remote peer ip address
         *            Port - Remote Peer udp port
         * Output   : Return 0 if successful 
         */
        int  SendTo(const void* Buffer, const size_t BufLen, std::string RemoteAddr, int Port);

        /*
         * Function : SendTo
         * Desc     : Send Buffer with size BufLen using RemoteAddr (called from server).
         * Input    : Buffer - bytes to be sent
         *            BufLen - Length of bytes to be sent
         *            RemoteAddr - sockaddr_in peer remote address. 
         *            Len - Length of sockaddr_in structure
         * Output   : Return 0 if successful, -1 otherwise
         */
        int  SendTo(const void* Buffer, const size_t BufLen, struct sockaddr_in &RemoteAddr, socklen_t Len);

        /*
         * Function : RecvFrom
         * Desc     : Receive Data and write into Buffer. RemoteAddr contains peer Ip address
         * Input    : Buffer - bytes read from socket
         *            BufferSize - Buffer size to store bytes
         *            RemoteAddr - Remote peer retrieved from ip source header
         *            RemoteAddrLen - Length of RemoteAddr structure
         * Output   : Return 0 if successful, -1 otherwise.
         */
        int  RecvFrom(void* Buffer, size_t BufferSize, struct sockaddr_in &RemoteAddr, socklen_t &RemoteAddrLen);

        /* 
         * Function : GetSockerFd
         * Desc     : Returns Socket FileDescriptor for listening 
         * Input    : None
         * Output   : File Descriptor 
         */
        int  GetSocketFd()
        {
            return m_SockFd;
        }

        /* Virtual destructor */
        ~UdpSocket()
        {
            close(m_SockFd);
        }

    private:
        /* Udp socket descriptor */
        int m_SockFd = -1;
};
