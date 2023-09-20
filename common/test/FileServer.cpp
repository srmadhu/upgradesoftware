#include <iostream>
#include <UdpSocket.hpp>
#include <FileReader.hpp>
#include <netinet/in.h> 

#define BUFSIZE 1024

int main()
{
    UdpSocket udpSkt;
    std::string fileName = "/tmptest.so";
    FileReader fr(fileName);
    struct sockaddr_in RemoteAddr;
    Msg_t msg;
    socklen_t Len = 0;
    char Buffer[BUFSIZE] = {0};
    int count = 0;
    std::string test = "testing hello back";
    udpSkt.BindSocket("127.0.0.1", 5000);
    udpSkt.RecvFrom(Buffer, sizeof(Buffer), RemoteAddr, Len);
    msg.type = MSG_SWDLFLNAME;
    msg.Buffer = "test.so";
    udpSkt.SendTo(Buffer, sizeof(Buffer), RemoteAddr, Len);
    while((count = fr.ReadFile(Buffer, 1024))>0)
    {
        udpSkt.SendTo(Buffer, count, RemoteAddr, Len);
    }

    return 0;
}
