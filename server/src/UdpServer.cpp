#include <iostream>
#include <UdpSocket.hpp>
#include <MsgFormat.hpp>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <cstring>
#include <UdpServer.hpp>

#define BUFSIZE 1024

UdpServer::UdpServer(std::string IpAddress, int Port)
{
    udpSkt.BindSocket(IpAddress, Port);
}
void UdpServer::Send(const void *Buffer, size_t BufLen)
{
    udpSkt.SendTo(Buffer, BufLen, RemoteAddr, Len);
}
void UdpServer::Recv(void *Buffer, size_t BufLen, std::string &PeerAddr)
{
    char str[INET_ADDRSTRLEN];
    udpSkt.RecvFrom(Buffer, BufLen, RemoteAddr, Len);
    inet_ntop(AF_INET, &(RemoteAddr.sin_addr), str, INET_ADDRSTRLEN);
    PeerAddr = str;
}
