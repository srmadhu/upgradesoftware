#include <UdpSocket.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

#define CHECK_VALID_FD   \
{                        \
    if (-1 == sockFd)    \
    {                    \
        std::cerr<<"Socket Initialization is not done"<<std::endl; \
        return -1;      \
    }                   \
}

int UdpSocket::CreateSocket()
{
    /* IPv4 protocol , UDP socket type, default 0 (no sniffing) */
    if ( -1 != (sockFd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        std::cout<<"Socket created "<<sockFd<<std::endl;
        return sockFd;
    } else {
        std::cerr<<"Socker creation failed "<<errno<<std::endl;
        return -1;
    }
}

int UdpSocket::BindSocket(std::string IpAddress, int Port)
{
    struct sockaddr_in servAddr;

    CHECK_VALID_FD;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(Port);
    if (IpAddress == "")
    {
        servAddr.sin_addr.s_addr = INADDR_ANY;
    }
    else
    {
        servAddr.sin_addr.s_addr = inet_addr(IpAddress.c_str());
    }
    

    if (0 == bind(sockFd, (const struct sockaddr *)&servAddr, sizeof(servAddr)))
    {
        std::cout<<"Socket Bind to "<<IpAddress<<":"<<Port
                    <<" is successful"<<std::endl;
         return true;
    } else {
        std::cerr<<"Socket Bind to "<<IpAddress<<":"<<Port
                    <<" failed"<<std::endl;
        return false;
    }
}
int UdpSocket::SendTo(const void* Buffer, const size_t BufLen, std::string IpAddress, int Port)
{
    int bytesSent = -1;
    int flags = 0;

    CHECK_VALID_FD;

    struct sockaddr_in RemoteAddr;
    RemoteAddr.sin_family = AF_INET;
    RemoteAddr.sin_port = htons(Port);
    RemoteAddr.sin_addr.s_addr = inet_addr(IpAddress.c_str());
    if ( 0 < (bytesSent = sendto(sockFd, Buffer, BufLen, flags,
                        (const struct sockaddr *) &RemoteAddr, sizeof(RemoteAddr))))
    {
        std::cout<<"Sent "<<bytesSent<<" bytes successfully"<<std::endl;
        return bytesSent;
    } else {
        std::cerr<<"Sent failed "<<errno<<std::endl;
        return -1;
    }
}
int UdpSocket::SendTo(const void* Buffer, const size_t BufLen, struct sockaddr_in &RemoteAddr, socklen_t Len)
{
    int bytesSent = -1;
    int flags = 0;

    CHECK_VALID_FD;

    if ( 0 < (bytesSent = sendto(sockFd, Buffer, BufLen, flags,
                        (const struct sockaddr *) &RemoteAddr, Len)))
    {
        std::cout<<"Sent "<<bytesSent<<" bytes successfully"<<std::endl;
        return bytesSent;
    } else {
        std::cerr<<"Sent failed "<<errno<<std::endl;
        return -1;
    }
}

int UdpSocket::RecvFrom(void * Buffer, size_t BufferSize, struct sockaddr_in &RemoteAddr, socklen_t &RemoteAddrLen)
{
    int bytesReceived = -1;
    int flags = 0;
    socklen_t addrLen;
    struct sockaddr_in remoteAddr;

    CHECK_VALID_FD;

    memset(&RemoteAddr, 0, sizeof(struct sockaddr_in));
    if ( 0 < (bytesReceived = recvfrom(sockFd, (char *) Buffer, BufferSize,
                                flags, (struct sockaddr *) &remoteAddr, 
                                &addrLen)))
    {
        std::cout<<"Received "<<bytesReceived<<" bytes succcessfully"<<std::endl;
        memcpy(&RemoteAddr, &remoteAddr, sizeof(remoteAddr));
        RemoteAddrLen = addrLen;
        return bytesReceived;
    } else {
        std::cout<<"Receive failed "<<errno<<std::endl;
        return -1;
    }
}
