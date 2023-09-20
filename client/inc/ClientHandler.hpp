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
        /* Function : HandleClientMessage 
         * Desc     : Handle messages received from server through any transport
         * Input    : Buffer - Buffer contains the message 
         *            BufLen - Length of the message received 
         *            PeerAddr - Peer Address or details 
         * Output   : None
         */
        void HandleClientMessage(void *Buffer, size_t BufLen, std::string PeerAddr = "");

        /* Function : HandleCliMessage 
         * Desc     : handles cli message from user 
         * Input    : cmdLine - command entered by user
         * Output   : None
         */
        void HandleCliMessage(std::string cmdLine);
        /* Function : RecvMessage
         * Desc     : Receiving message from peer - pure virtual
         * Input    : None
         * Output   : None
         */
        virtual void RecvMessage() = 0;
        /* Function : SendMessage
         * Desc     : Send message to peer - pure virtual 
         * Input    : Buffer - Message to be sent
         *            Len - length of the message
         * Output   : None
         */
        virtual void SendMessage(void *buffer, size_t Len)=0;
        /* Function : GetClientState
         * Desc     : Retrieve current state of state machine
         * Input    : None
         * Output   : None
         */
        StateEnum GetClientState()
        {
            return m_ClientState;
        }
        /* Function : Timercallback
         * Desc     : Timer callback called after every 10s
         * Input    : None
         * Output   : None
         */
        void TimerCallback()
        {
            if ( GetClientState() == CL_STATE_REGISTER ||
                            GetClientState() == CL_STATE_INIT)
            {
                SendRegister();
            }
        }
        /* Function : SetClientState
         * Desc     : Set state for state machine
         * Input    : State - State to be set
         * Output   : None
         */
        void SetClientState(StateEnum State)
        {
            m_ClientState = State;
        }
        /* Function : SendRegister
         * Desc     : Send Register request to server
         * Input    : None
         * Output   : None
         */
        void SendRegister()
        {
            UpdateMsg_t msg;
            memset(&msg, 0, sizeof(msg));
            msg.msgType = MSG_CLREGISTER;
#ifdef DEBUG
            std::cout<<"ClientHandler: Sending Register request "<<std::endl;
            std::cout<<"ClientHandler: Changing state to Register"<<std::endl;
#endif
            SendMessage(&msg, sizeof(msg));
            SetClientState(CL_STATE_REGISTER);
        }

    protected:
        /* Constructor */
        ClientHandler(): m_ClientState(CL_STATE_INIT)
        {
#ifdef DEBUG
            std::cout<<"ClientHandler:: constructor is called"<<std::endl;
#endif
            verify_class_dlopen();
        }
        /* Virtual Destructor */
        virtual ~ClientHandler()
        {
           m_FileName = "";
           m_ClientState = CL_STATE_EXIT;
        }

    private:
        /* File Writer to create local file */
        FileWriter m_FileWriter;
        /* FileName downloaded from server */
        std::string m_FileName = "";
        /* Client state machine */
        StateEnum m_ClientState;
};
