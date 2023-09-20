#include <iostream>
#include <UdpSocket.hpp>
#include <MsgFormat.hpp>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <cstring>
#include <UdpServer.hpp>

#define BUFSIZE 1024
/* Function : Constructor
 * Desc     : UdpServer constructor 
 * Input    : IpAddress - IP Address
 *            Port  - Port
 * Output   : None
 */
UdpServer::UdpServer(std::string IpAddress, int Port)
{
    m_UdpSkt.BindSocket(IpAddress, Port);
}
/* Function : Send
 * Desc     : Sending Buffer with BufferLen
 * Input    : Buffer - Message to be sent
 *            BufLen - Message length
 * Output   : None
 */
void UdpServer::Send(const void *Buffer, size_t BufLen)
{
    m_UdpSkt.SendTo(Buffer, BufLen, m_RemoteAddr, m_Len);
}
/* Function : Recv
 * Desc     : Receiving Buffer from remote client
 * Input    : Buffer - Message received from client
 *            BufLen - Message length
 *            PeerAddr - Peer Address
 * Output   : None
 */
void UdpServer::Recv(void *Buffer, size_t BufLen, std::string &PeerAddr)
{
    char str[INET_ADDRSTRLEN];
    m_UdpSkt.RecvFrom(Buffer, BufLen, m_RemoteAddr, m_Len);
    inet_ntop(AF_INET, &(m_RemoteAddr.sin_addr), str, INET_ADDRSTRLEN);
    PeerAddr = str;
}
