/*
 *  File: UpdateServer.cpp
 *  
 *      Main file for service side of upgrade software 
 */

#include <ServerHandler.hpp>

static constexpr int DEFAULT_PORT = 5656;

int main(int argc, char * argv[])
{
    int Port = DEFAULT_PORT;

    try 
    {
        if (argc == 2)
        {
            Port = std::stoi(argv[1]);
        } 
    } catch ( const std::exception e)
    {
        std::cout<<"Exception : "<<e.what()<<" occured. Using Default Port(5656)."<<std::endl;
        Port = DEFAULT_PORT;
    }

    ServerHandler& servHandler = ServerHandler::Instance(Port);
    servHandler.HandleEvents();
    return EXIT_SUCCESS;
}
