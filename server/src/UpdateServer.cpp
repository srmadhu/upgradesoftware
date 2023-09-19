#include <iostream>
#include <UdpSocket.hpp>
#include <UdpServer.hpp>
#include <MsgFormat.hpp>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <cstring>
#include <FileReader.hpp>
#include <iterator>
#include <vector>
#include <sstream>

#define NEWBUFSIZ 1024

class UpdateServer
{
    public:
        UpdateServer() = delete;
        UpdateServer(std::string IpAddress, int Port): udpServ(IpAddress, Port)
        {
        }
        UpdateServer(int Port): udpServ("", Port)
        {
            std::cout<<"Listen on all ip address "<<std::endl;
        }
        void HandleClientMessage(void *Buffer, size_t BufLen, std::string PeerAddr)
        {
            UpdateMsg_t *msg = (UpdateMsg_t *) Buffer;

            switch(msg->msgType)
            {
                case MSG_REGISTER:
                {
                    std::cout<<"Register Request Received from "<<PeerAddr<<std::endl;
                    UpdateMsg_t msg;
                    msg.msgType = MSG_REGDONE;
                    udpServ.Send(&msg, sizeof(msg));
                    break;
                }
                case MSG_DEREGISTER:
                {
                    std::cout<<"Register Request Received from "<<PeerAddr<<std::endl;
                    break;
                }

            }
        }
        void HandleCliMessage(std::string cmdLine)
        {
            std::stringstream ss(cmdLine);
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;
            std::vector<std::string> cmd(begin, end);
            if (cmd.size() != 2)
            {
                std::cout<<"Usage: push <filename>"<<std::endl;
                return ;
            }
            int bytesRead = -1;
            int count = 0;
            if (cmd[0] == PUSH_COMMAND)
            {
                char Buffer[NEWBUFSIZ]={0};
                UpdateMsg_t msg;

                msg.msgType = MSG_FILENAME;
                strncpy(msg.Buffer, cmd[1].c_str(), cmd[1].length());
                msg.Length = cmd[1].length();

                udpServ.Send(&msg, sizeof(msg));
                std::string FileName = "/tmp/";
                FileName += cmd[1];
                FileReader fr(FileName);
                while( (bytesRead = fr.ReadFile(Buffer, sizeof(Buffer))) > 0)
                {
                    UpdateMsg_t msg;
                    msg.msgType = MSG_SENDFILE;
                    memcpy(msg.Buffer, Buffer, bytesRead);
                    msg.counter = ++count;
                    std::cout<<"Sending "<<bytesRead<<"count = "<<msg.counter<<std::endl;
                    msg.Length = bytesRead;
                    udpServ.Send(&msg, sizeof(msg));
                }

                msg.msgType = MSG_FILEEND;
                udpServ.Send(&msg, sizeof(msg));
            }
        }
        void HandleEvents()
        {
            fd_set readFdSet;
            int maxfd = 0;
            FD_ZERO(&readFdSet);

            int udpFd = udpServ.GetSocketFd();
            
            maxfd = std::max(udpFd, 0) + 1;
            
            while (1)
            {
                int ready = 0, Len = 0;
                FD_SET(udpFd, &readFdSet);
                FD_SET(fileno(stdin), &readFdSet);
                ready = select(maxfd, &readFdSet, NULL, NULL, NULL);
                
                if (FD_ISSET(udpFd, &readFdSet))
                {
                    UpdateMsg_t msg;
                    size_t Len = sizeof(msg);
                    std::string PeerAddr;
                    std::cout<<"udp fd is set "<<std::endl;
                    udpServ.Recv(&msg, Len, PeerAddr);
                    HandleClientMessage(&msg, Len, PeerAddr);
                }
                else if (FD_ISSET(fileno(stdin), &readFdSet))
                {
                    #define MAX_CMD_LENGTH 50
                    char cmdInput[MAX_CMD_LENGTH];
                    std::cin.getline(cmdInput, sizeof(cmdInput));
                    std::string input(cmdInput);
                    std::cout<<"standard input is set "<<input<<std::endl;
                    std::cout<<"Pusing software to client "<<std::endl;
                    if (input == "exit")
                        return;
                    HandleCliMessage(input);
                }
            }
            
        }
    private:
        /* Transport is UDP. This can be factory of transport machanisms. */
        UdpServer udpServ;

};


int main()
{
    int Port =5656;
    UpdateServer updServ(Port);
    updServ.HandleEvents();
    return 0;
}
