#pragma once 
#include <iostream>
#include <UdpSocket.hpp>
#include <MsgFormat.hpp>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <cstring>


class UdpServer
{
    public:
        /* UdpServer constructor */
        UdpServer(std::string IpAddress, int Port);
        /* UdpServer with port*/
        UdpServer(int Port);
        /* Function : Send
         * Desc     : Sending Buffer with BufferLen
         * Input    : Buffer - Message to be sent
         *            BufLen - Message length
         * Output   : None
         */
        void Send(const void *Buffer, size_t BufLen);
        /* Function : Recv
         * Desc     : Receiving Buffer from remote client
         * Input    : Buffer - Message received from client
         *            BufLen - Message length
         *            PeerAddr - Peer Address
         * Output   : None
         */
        void Recv(void *Buffer, size_t BufLen, std::string &PeerAddr);
        /* Function : GetSocktetFd
         * Desc     : Retrieve socket fd
         * Input    : None
         * Output   : Socket descriptor 
         */
        int GetSocketFd()
        {
           return m_UdpSkt.GetSocketFd();
        }
    private:
        /* Udp Socket descriptor*/
        UdpSocket m_UdpSkt; 
        /* Remote Address */
        struct  sockaddr_in m_RemoteAddr;
        /* Remote Address length */
        socklen_t m_Len;
};
