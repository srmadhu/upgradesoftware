#pragma once 
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
#include <MsgFormat.hpp>

#define BUFSIZE 1024

/* dlopen */
#include <gnu/lib-names.h>
#include <dlfcn.h>
#include <ActionReceiver.hpp>
#include <pthread.h>
   
#define PORT     8080
#define MAXLINE 1024

void verify_class_dlopen();

class ClientHandler
{
    public:
        void HandleClientMessage(void *Buffer, size_t BufLen, std::string PeerAddr = "");
        void HandleCliMessage(std::string cmdLine);
        virtual void HandleEvents() = 0;
        StateEnum GetClientState()
        {
            return m_ClientState;
        }
        void SetClientState(StateEnum state)
        {
            m_ClientState = state;
        }

    protected:
        ClientHandler(): m_ClientState(CL_STATE_INIT)
        {
            verify_class_dlopen();
        }
        virtual ~ClientHandler()
        {
           m_FileName = "";
           m_ClientState = CL_STATE_EXIT;
        }

    private:
        FileWriter m_FileWriter;
        std::string m_FileName = "";
        StateEnum m_ClientState;
};
