#include <UdpSocket.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

#define CHECK_VALID_FD   \
{                        \
    if (-1 == m_SockFd)    \
    {                    \
        std::cerr<<"Socket Initialization is not done"<<std::endl; \
        return -1;      \
    }                   \
}

/* 
 * Function : CreateSocket
 * Desc     : Create Udp Socket for Server or Client 
 * Input    : None
 * Output   : Socket Descriptor if successful, -1 otherwise
 */
int UdpSocket::CreateSocket()
{
    /* IPv4 protocol , UDP socket type, default 0 (no sniffing) */
    if ( -1 != (m_SockFd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
 #ifdef DEBUG
        std::cout<<"Socket created "<<m_SockFd<<std::endl;
 #endif
        return m_SockFd;
    } else {
        std::cerr<<"Socker creation failed "<<errno<<std::endl;
        return -1;
    }
}

/* 
 * Function : BindSocket
 * Desc     : Binding Socket to specific IP and Port. Mostly
 *      called from server but applicable to client also.
 * Input    : IpAddress - Local IpAddress to bind
 *            Port - Port to bind
 * Output   : Socket Descriptor if successful, -1 otherwise
 */
int UdpSocket::BindSocket(const std::string IpAddress, int Port)
{
    struct sockaddr_in servAddr;

    CHECK_VALID_FD;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(Port);

    /*If no Ip provied, bind to all ip address */
    if (IpAddress == "")
    {
        servAddr.sin_addr.s_addr = INADDR_ANY;
    }
    else
    {
        servAddr.sin_addr.s_addr = inet_addr(IpAddress.c_str());
    }
    
    /* Bind to local IP address */
    if (0 == bind(m_SockFd, (const struct sockaddr *)&servAddr, sizeof(servAddr)))
    {
#ifdef DEBUG
        std::cout<<"Socket Bind to "<<IpAddress<<":"<<Port
                    <<" is successful"<<std::endl;
 #endif
         return true;
    } else {
        std::cerr<<"Socket Bind to "<<IpAddress<<":"<<Port
                    <<" failed"<<std::endl;
        return false;
    }
}

/*
 * Function : SendTo
 * Desc     : Send Buffer with size BufLen to RemoteAddr:Port
 * Input    : Buffer - bytes to be sent
 *            BugLen - Length of bytes to be sent
 *            RemoteAddr - Remote peer ip address
 *            Port - Remote Peer udp port
 * Output   : Return 0 if successful 
 */
int UdpSocket::SendTo(const void* Buffer, const size_t BufLen, std::string IpAddress, int Port)
{
    int bytesSent = -1;
    int flags = 0;

    CHECK_VALID_FD;

    struct sockaddr_in RemoteAddr;
    RemoteAddr.sin_family = AF_INET;
    RemoteAddr.sin_port = htons(Port);
    RemoteAddr.sin_addr.s_addr = inet_addr(IpAddress.c_str());
    if ( 0 < (bytesSent = sendto(m_SockFd, Buffer, BufLen, flags,
                        (const struct sockaddr *) &RemoteAddr, sizeof(RemoteAddr))))
    {
#ifdef DEBUG
        std::cout<<"Sent "<<bytesSent<<" bytes successfully"<<std::endl;
#endif
        return bytesSent;
    } else {
        std::cerr<<"Send1 failed "<<errno<<std::endl;
        return -1;
    }
}

/*
 * Function : SendTo
 * Desc     : Send Buffer with size BufLen using RemoteAddr (called from server).
 * Input    : Buffer - bytes to be sent
 *            BufLen - Length of bytes to be sent
 *            RemoteAddr - sockaddr_in peer remote address. 
 *            Len - Length of sockaddr_in structure
 * Output   : Return 0 if successful, -1 otherwise
 */
int UdpSocket::SendTo(const void* Buffer, const size_t BufLen, struct sockaddr_in &RemoteAddr, socklen_t Len)
{
    int bytesSent = -1;
    int flags = 0;

    CHECK_VALID_FD;

    if ( 0 < (bytesSent = sendto(m_SockFd, Buffer, BufLen, flags,
                        (const struct sockaddr *) &RemoteAddr, Len)))
    {
#ifdef DEBUG
        std::cout<<"Sent "<<bytesSent<<" bytes successfully"<<std::endl;
#endif
        return bytesSent;
    } else {
        std::cerr<<"Send2 failed "<<errno<<std::endl;
        return -1;
    }
}

/*
 * Function : RecvFrom
 * Desc     : Receive Data and write into Buffer. RemoteAddr contains peer Ip address
 * Input    : Buffer - bytes read from socket
 *            BufferSize - Buffer size to store bytes
 *            RemoteAddr - Remote peer retrieved from ip source header
 *            RemoteAddrLen - Length of RemoteAddr structure
 * Output   : Return 0 if successful, -1 otherwise.
 */
int UdpSocket::RecvFrom(void * Buffer, size_t BufferSize, struct sockaddr_in &RemoteAddr, socklen_t &RemoteAddrLen)
{
    int bytesReceived = -1;
    int flags = 0;
    socklen_t addrLen;
    struct sockaddr_in remoteAddr;

    CHECK_VALID_FD;

    memset(&RemoteAddr, 0, sizeof(struct sockaddr_in));
    if ( 0 < (bytesReceived = recvfrom(m_SockFd, (char *) Buffer, BufferSize,
                                flags, (struct sockaddr *) &remoteAddr, 
                                &addrLen)))
    {
#ifdef DEBUG
        std::cout<<"Received "<<bytesReceived<<" bytes succcessfully"<<std::endl;
#endif
        memcpy(&RemoteAddr, &remoteAddr, sizeof(remoteAddr));
        RemoteAddrLen = addrLen;
        return bytesReceived;
    } else {
        std::cerr<<"Receive failed "<<errno<<std::endl;
        return -1;
    }
}
