#pragma once
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

class ServerHandler
{
    public:
        /* No default constructor */
        ServerHandler() = delete;
        /* Function : HandleClientMessage
         * Desc     : Received client message handler
         * Input    : Buffer - Received message
         *            BufLen - Length of recived message
         *            PeerAddr - Remote Peer Address
         * Outpu    : None
         */
        void HandleClientMessage(void *Buffer, size_t BufLen, std::string PeerAddr);
        /* Function : HandleCliMessage
         * Desc     : cmdLine to handled from cli
         * Input    : cmdLine - command Line 
         * Output   : None
         */
        void HandleCliMessage(std::string cmdLine);
        /* Function : HandleEvents
         * Desc     : Handling events from remote peer
         * Input    : None
         * Output   : None
         */
        void HandleEvents();
        /* Function : Instance
         * Desc     : Create Server Handler instance
         * Input    : Port number 
         * Output   : Server Handler
         */
        static ServerHandler& Instance(int Port)
        {
            static ServerHandler srvHandler(Port);
            return srvHandler;
        }

    private:
        /* Constructor to fill IPaddress */
        ServerHandler(std::string IpAddress, int Port): m_UdpServ(IpAddress, Port)
        {
#ifdef DEBUG
            std::cout<<"Listening on "<<IpAddress<<std::endl;
#endif
        }
        /* Constructore to fill Port */
        ServerHandler(int Port): m_UdpServ("", Port)
        {
#ifdef DEBUG
            std::cout<<"Listen on all ip address "<<std::endl;
#endif
        }
       /* Transport is UDP. This can be factory of transport machanisms. */
        UdpServer m_UdpServ;

};
