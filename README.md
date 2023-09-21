# upgradesoftware
Upgrade Software
   Upgrade software is based on client-server model. Client is a machine where functionality to 
be installed to provide new features. Server stores software either in the form of 
installer. Client installed with default software version shipped with package.
Server CLI supports push command to push new software to registered client. 

Alternatives/Limitations:
    * UDP transport used between client and server to reduce packer traffic due to 
        TCP keep alives and session maintanence. 
        - ClientHandler can be extended with different transport mechanisms to send/receive
        packets from/to server. 
    * Server CLI added to support simplified push action. Alternatvie approach isto use 
        another application connect to server through message query to execute push action. 
    * Used libfunctional.so to implement functional part and used dyamic loading to support
        print version without client application restart. 
        Alternative: Use another agent application connect through message queue and restart when 
        client downloads new library. 
    * Implement docker images for client and server to run in different environments. 
    * Only single client is supported. 
    
      
Improvements:
    * Support Ipv6 transport along with Ipv4. 
    * Encrypt software using client's public key before sending to client and decrypt using 
        private key. This requires openssl library support. 
    * Client/Server can support configuration file for parameters like enable secure transfer. 
    * Client software upgrade module to support X platform. 
    * Support multiple clients in server to push software to all registered clients.
    * Packaging with rpm/dpkg and install it after downloading. 
    * Support push of latest software when client registers with server. 
    * Server maintains registered client list with timeout and requires client to renew in interval.
    * Server support query of software version from all clients and push latest software if requried. 
    * Client provide option to upgrade later after downloading. 
    * Server load balancing.

To Download Source:
    git clone https://github.com/srmadhu/upgradesoftware.git

To Compile:
    Execute "make" to compile client, server and common modules. 

To Package:
    Client: <TOPLEVEL>/Package_Client.sh
    Server: <TOPLEVEL>/Package_Server.sh

Installer:
    Client: nxt_client.tgz
    Server: nxt_server.tgz

To Run Server:
    tar -xvzf nxt_server.tgz
    cd nxt/server/bin/
    ./UpdateServer.sh <ServerPort>
        E.g., ./UpdateServer.sh 5467

To Run Client:
    tar -xzvf nxt_client.tgz
    cd nxt/client/bin
    ./UpdateClient.sh <ServerIp> <ServerPort>
        E.g., ./UpdateClient.sh 127.0.0.1 5467

To push new Software from Server CLI:
    push <filename>
    E.g., push libfunctional_1_0.so

Outupt:
---------

Server:
ubuntu@ip-172-26-10-234:~/install/nxt/server/bin$ ./UpdateServer.sh 5467

NxtServer#
NxtServer# push libfunctional_1_0.so

NxtServer# push libfunctional_2_0.so

NxtServer# exit
ubuntu@ip-172-26-10-234:~/install/nxt/server/bin$


Client:
ubuntu@ip-172-26-10-234:~/install/nxt/client/bin$ ./UpdateClient.sh 127.0.0.1 5467
// Default version after install
product version :
Major = 5
Minor = 6
productName = nxtgen

// After Pusing libfunctional_1_0.so from server 
NxtClient#
product version :
Major = 5
Minor = 6
productName = nxtgen

// After Pusing libfunctional_2_0.so from server 
product version :
Major = 8
Minor = 6
productName = nxtgen

exit
ubuntu@ip-172-26-10-234:~/install/nxt/client/bin$



    
 
