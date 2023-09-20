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
        /* Function : Send
         * Desc     : Send message to server 
         * Input    : Buffer - Message to be sent to server
         *            BufLen - Length of the message
         * Output   : None
         */
        void Send(const void *Buffer, size_t BufLen);
        /* Function : Recv
         * Desc     : Receive message from server
         * Input    : Buffer - Message received from server
         *            BufLen - Length of the message
         * Output   : None
         */
        void Recv(void *Buffer, size_t BufLen, std::string &PeerAddr);
        /* Function : GetSocketFd
         * Desc     : Retrieve Socket Fd
         * Input    : None
         * Output   : Socket Fd
         */
        int GetSocketFd()
        {
            return m_UdpSkt.GetSocketFd();
        }

    private:
        /* Udp Socket*/
        UdpSocket m_UdpSkt;
        /* Remote address info */
        struct sockaddr_in m_RemoteAddr;
        /* Length of socket address */
        socklen_t m_Len;
};

