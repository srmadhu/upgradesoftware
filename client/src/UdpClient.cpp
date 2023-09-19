#include <iostream>
#include <UdpSocket.hpp>
#include <MsgFormat.hpp>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <cstring>
#include <UdpClient.hpp>

#define BUFSIZE 1024

UdpClient::UdpClient(std::string IpAddress, int Port)
{
    std::cout<<"Store "<<IpAddress<<":"<<Port<<" in UdpClient object "<<std::endl;
    RemoteAddr.sin_family = AF_INET;
    RemoteAddr.sin_port = htons(Port);
    RemoteAddr.sin_addr.s_addr = inet_addr(IpAddress.c_str());
    Len = sizeof(RemoteAddr);
}
void UdpClient::Send(const void *Buffer, size_t BufLen)
{
    udpSkt.SendTo(Buffer, BufLen, RemoteAddr, Len);
}
void UdpClient::Recv(void *Buffer, size_t BufLen, std::string &PeerAddr)
{
    char str[INET_ADDRSTRLEN];
    udpSkt.RecvFrom(Buffer, BufLen, RemoteAddr, Len);
    inet_ntop(AF_INET, &(RemoteAddr.sin_addr), str, INET_ADDRSTRLEN);
    PeerAddr = str;
}


