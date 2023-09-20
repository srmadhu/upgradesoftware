#include <iostream>
#include <UdpSocket.hpp>
#include <UdpClient.hpp>
#include <MsgFormat.hpp>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <cstring>
#include <FileWriter.hpp>
#include <iterator>
#include <vector>
#include <sstream>
#include <string>
#include <unistd.h>
#include <ClientHandler.hpp>

#define BUFSIZE 1024

/* dlopen */
#include <gnu/lib-names.h>
#include <dlfcn.h>
#include <ActionReceiver.hpp>
#include <UdpClientHandler.hpp>
#include <pthread.h>
   
#define PORT     8080
#define MAXLINE 1024

/* Function : RecvMessage
 * Desc     : Recv message from remote peer. Handles
 *              action handling for the message.
 * Input    : None
 * Len      : None
 */
void UdpClientHandler::RecvMessage()
{
    std::cout<<std::endl<<"NxtClient# ";
    for(;;)
    {
        int ready = 0, maxFd = 0;
        int udpFd = m_UdpClt.GetSocketFd();
        struct timeval tv;
        fd_set readFdSet;
        maxFd = std::max(udpFd, 0) + 1;


        /* Handle both server messages and user input */
        FD_ZERO(&readFdSet);
        FD_SET(udpFd, &readFdSet);
        FD_SET(fileno(stdin), &readFdSet);
        tv.tv_sec = 10; tv.tv_usec = 0;
        std::cout.flush();
        ready = select(maxFd, &readFdSet, NULL, NULL, &tv);

        TimerCallback();
        /* if select returned error, still continue */
        if (ready < 0)
        {
            std::cerr<<"Select return socket error : "<<errno<<std::endl;
            continue;
        } 
                
        if (FD_ISSET(udpFd, &readFdSet))
        {
            UpdateMsg_t  msg;
            size_t Len = sizeof(msg);
            std::string PeerAddr;
            m_UdpClt.Recv(&msg, Len, PeerAddr);
            HandleClientMessage(&msg, Len, PeerAddr);
        }
        else if (FD_ISSET(fileno(stdin), &readFdSet))
        {
            std::string cmdInput;
            std::getline(std::cin, cmdInput);
            if ( cmdInput  == "show version")
            {
                verify_class_dlopen();
            }
            else if ( cmdInput == "exit")
            {
                return;
            }
            std::cout<<std::endl<<"NxtClient# ";
        }
    }
    return;
}
