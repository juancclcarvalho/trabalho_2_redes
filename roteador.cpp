#include <iostream>
#include <string>

#include <arpa/inet.h>
#include <netinet/in.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include "routing_table.hpp"

int main(int argc, char const *argv[])
{  
    if(argc < 3)
    {
        std::cout << "USAGE: PORT destination/mask/gateway/interface ... destination/mask/gateway/interface";
    }
    // cria tabela de roteamento (o construtor faz toda essa lógica pra gente)
    routing_table_t routing_table(argc, argv);
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr, cliaddr;
       
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
       
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
       
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(atoi(argv[1]));
       
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
       
    int n;
    socklen_t len;
    IPv4Header_t* header = (IPv4Header_t*)&buffer[0];
    char* data = &buffer[sizeof(IPv4Header_t)];
    uint32_t* forwardIP = new uint32_t;
    uint32_t* forwardPort = new uint32_t;

    while(true)
    {
        len = sizeof(cliaddr);
        // receives packet
        n = recvfrom(sockfd, (char *)buffer, 1024,  MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);

        // gets TTL
        int TTL = header->getTTl() - 1;
        if(!TTL)
        {
            std::cout << "Time to Live exceeded in Transit, dropping packet for " << ipBinaryToDecimal(header->getDestinationAddress()) << '\n';
            continue;
        }

        // chooses next route, saves forward address in forwardIP pointer and does the same with the port
        // function a boolean depending on whether or not have we found an address to forward the packet to
        // the implementation is in "routing_table.cpp"
        if(routing_table.choose_route(header->getDestinationAddress(), forwardIP, forwardPort))
        {
            if(*forwardIP ) // when forwardIp is nonzero, it means we've got an indirect routing
            {
                std::cout << "forwarding packet for " << ipBinaryToDecimal(header->getDestinationAddress()) << " to next hop " <<
                                                      << ipBinaryToDecimal(forwardIP) << " over interface " << forwardPort << '\n';
            }
            else // direct routing
            {
                std::cout << "destination reached. From " << ipBinaryToDecimal(header->getSourceAddress()) << " to " 
                                                          << ipBinaryToDecimal(header->getDestinationAddress()) << ": " << data << '\n'; 
            }
           
        }
        else
        {
            std::cout << "destination " << ipBinaryToDecimal(header->getDestinationAddress()) << " not found in routing table, dropping packet"
        }
    }


    return 0;
}
