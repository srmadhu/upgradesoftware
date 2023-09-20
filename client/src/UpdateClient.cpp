#include <UdpClientHandler.hpp>


void PrintUsage(std::string ProgName)
{
    std::cout<<"Usage: "<<basename(ProgName.c_str())<<" <Server_Ip_Address> <Port> "<<std::endl;
    std::cout<<"\tServer_Ip_Address  - Server IP Address "<<std::endl;
    std::cout<<"\tPort - Udp Port "<<std::endl;
}


int main(int argc, char* argv[])
{
    std::string IpAddress = ""; 
    int Port = 0;
    if (argc != 3)
    {
        PrintUsage(argv[0]);
        return 0;
    }

    try 
    {
        IpAddress = argv[1];
        Port = std::stoi(argv[2]);
    } catch (const std::exception e)
    {
        std::cout<<"Exception : "<<e.what()<<" occured."<<std::endl;
        return EXIT_FAILURE;
    }
#ifdef DEBUG
    std::cout<<"Main:: Connecting to Server "<<IpAddress<<":"<<Port<<std::endl;
#endif

    UdpClientHandler& cltHandler = UdpClientHandler::Instance(IpAddress, Port);
    cltHandler.RecvMessage();
    return EXIT_SUCCESS;
}
