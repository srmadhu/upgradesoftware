#include <ServerHandler.hpp>

#define NEWBUFSIZ 1024

void ServerHandler::HandleClientMessage(void *Buffer, size_t BufLen, std::string PeerAddr)
{
    UpdateMsg_t *msg = (UpdateMsg_t *) Buffer;

    switch(msg->msgType)
    {
        case MSG_CLREGISTER:
        {
            std::cout<<"Register Request Received from "<<PeerAddr<<std::endl;
            UpdateMsg_t msg;
            msg.msgType = MSG_CLREGDONE;
            udpServ.Send(&msg, sizeof(msg));
            break;
        }
        case MSG_CLDEREGISTER:
        {
            std::cout<<"Register Request Received from "<<PeerAddr<<std::endl;
            break;
        }
    }
}
void ServerHandler::HandleCliMessage(std::string cmdLine)
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

        msg.msgType = MSG_SWDLFLNAME;
        strncpy(msg.Buffer, cmd[1].c_str(), cmd[1].length());
        msg.Length = cmd[1].length();

        udpServ.Send(&msg, sizeof(msg));
        std::string FileName = "/tmp/";
        FileName += cmd[1];
        FileReader fr(FileName);
        while( (bytesRead = fr.ReadFile(Buffer, sizeof(Buffer))) > 0)
        {
            UpdateMsg_t msg;
            msg.msgType = MSG_SWDLFILE;
            memcpy(msg.Buffer, Buffer, bytesRead);
            msg.Length = bytesRead;
            udpServ.Send(&msg, sizeof(msg));
        }

        msg.msgType = MSG_SWDLCMPT;
        udpServ.Send(&msg, sizeof(msg));
    }
}
void ServerHandler::HandleEvents()
{
 
    for(;;)
    {
        int ready = 0, maxFd = 0;
        int udpFd = udpServ.GetSocketFd();
        struct timeval tv;
        fd_set readFdSet;
        
        /* Handle both client messages and user input */
        FD_ZERO(&readFdSet);
        FD_SET(udpFd, &readFdSet);
        FD_SET(fileno(stdin), &readFdSet);
        maxFd = std::max(udpFd, 0) + 1;
        tv.tv_sec = 10; tv.tv_usec = 0;
        std::cout<<std::endl<<"NxtServer# ";
        std::cout.flush();
        ready = select(maxFd, &readFdSet, NULL, NULL, NULL);

        /* if select returned error, still continue; */
        if ( ready < 0)
        {
            std::cout<<"Select return socket error : "<<errno<<std::endl;
            continue;
        }
 
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

