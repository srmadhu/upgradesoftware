#include <iostream>
#include <UdpSocket.hpp>
#include <netinet/in.h> 
#include <MsgFormat.hpp>
#include <cstring>

#define BUFSIZE 1024


void UpdateHandler::RegisterClient(UdpSocket &udpSkt)
{
    std::string test = "testing hello";
    Msg_t msg;
    msg.msgType = MSG_REGISTER;
    strncpy(msg.Buffer, test.c_str(), sizeof(msg.Buffer));
    udpSkt.SendTo((const char *)&msg,sizeof(msg), "127.0.0.1", 5000);
}
void UpdateHandler::DeRegister(UdpSocket &udpSkt)
{
    std::string test = "testing hello";
    Msg_t msg;
    msg.msgType = MSG_DEREGISTER;
    strncpy(msg.Buffer, test.c_str(), sizeof(msg.Buffer));
    udpSkt.SendTo((const char *)&msg,sizeof(msg), "127.0.0.1", 5000);
}

void UpdateHandler::SendFileName(UdpSocket &udpSkt)
{
    std::string test = "testing hello";
    Msg_t msg;
    msg.msgType = MSG_FILENAME;
    strncpy(msg.Buffer, test.c_str(), sizeof(msg.Buffer));
    udpSkt.SendTo((const char *)&msg,sizeof(msg), "127.0.0.1", 5000);
}
void UpdateHandler::SendFile(UdpSocket &udpSkt)
{
    std::string test = "testing hello";
    Msg_t msg;
    msg.msgType = MSG_SENDFILE;
    strncpy(msg.Buffer, test.c_str(), sizeof(msg.Buffer));
    udpSkt.SendTo((const char *)&msg,sizeof(msg), "127.0.0.1", 5000);
}
void UpdateHandler::SendFileEnd(UdpSocket &udpSkt)
{
    std::string test = "testing hello";
    Msg_t msg;
    msg.msgType = MSG_FILEEND;
    strncpy(msg.Buffer, test.c_str(), sizeof(msg.Buffer));
    udpSkt.SendTo((const char *)&msg,sizeof(msg), "127.0.0.1", 5000);
}


int main()
{
    UdpSocket udpSkt;
    std::string newfileName = "/tmp/newtest.so";
    struct sockaddr_in RemoteAddr;
    unsigned int len = 0;
    char Buffer[BUFSIZE] = {0};
    Register(udpSkt);
    udpSkt.RecvFrom(Buffer, sizeof(Buffer), RemoteAddr, len);

    return 0;
}
