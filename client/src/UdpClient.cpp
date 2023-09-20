#include <UdpClient.hpp>

#define BUFSIZE 1024

UdpClient::UdpClient(std::string IpAddress, int Port)
{
#ifdef DEBUG
    std::cout<<"Store "<<IpAddress<<":"<<Port<<" in UdpClient object "<<std::endl;
#endif
    m_RemoteAddr.sin_family = AF_INET;
    m_RemoteAddr.sin_port = htons(Port);
    m_RemoteAddr.sin_addr.s_addr = inet_addr(IpAddress.c_str());
    m_Len = sizeof(m_RemoteAddr);
}
void UdpClient::Send(const void *Buffer, size_t BufLen)
{
    m_UdpSkt.SendTo(Buffer, BufLen, m_RemoteAddr, m_Len);
}
void UdpClient::Recv(void *Buffer, size_t BufLen, std::string &PeerAddr)
{
    char str[INET_ADDRSTRLEN];
    m_UdpSkt.RecvFrom(Buffer, BufLen, m_RemoteAddr, m_Len);
    inet_ntop(AF_INET, &(m_RemoteAddr.sin_addr), str, INET_ADDRSTRLEN);
    PeerAddr = str;
}


