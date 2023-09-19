#include <iostream>

#pragma once

class UpdateServerHandler
{
    public:
        updateHandler(string RemoteInfo)
        {
        }
        void RegisterClient();
        void DeregisterClient();
        void SendFileName();
        void SenFile();
        void SendFileEnd();
    private:
        UdpSocket udpSkt;
        FileReader fileReader;
        FileWrite fileWriter;
};
