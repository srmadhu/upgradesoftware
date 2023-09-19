#include <iostream>
#include <ClientHandler.hpp>


void PrintUsage(std::string ProgName)
{
    std::cout<<"Usage: "<<basename(ProgName.c_str())<<" <Server_Ip_Address> <Port> "<<std::endl;
    std::cout<<"\tServer_Ip_Address  - Server IP Address "<<std::endl;
    std::cout<<"\tPort - Udp Port "<<std::endl;
}


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        PrintUsage(argv[0]);
        return 0;
    }
    std::string IpAddress = argv[1];
    int Port = std::stoi(argv[2]);

    std::cout<<"Main:: Connecting to Server "<<IpAddress<<":"<<Port<<std::endl;

    ClientHandler clientHandler(IpAddress, Port);
    clientHandler.HandleEvents();
    return 0;
}
