#include <iostream>
#include <string>

#include <arpa/inet.h>
#include <netinet/in.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include "IPv4Header.hpp"

int main(int argc, char const *argv[])
{
    if(argc != 6)
    {
        std::cout << "Usage: ROUTER_IP   PORT   SOURCE_IP   DESTINATION_IP   CONTENT\n";
        return 0;
    }

    for(int i = 1 ; i <= 4; i++)
    {
        if(i == 2) continue;
        if(!isValidIp(std::string(argv[i]) ))
        {
            std::cout << '"' << argv[i] << '"' << " is not a valid ip address\nEXITING\n";
            return 0;
        }
        
    }
    // instantiates header data structure
    IPv4Header_t* header = new IPv4Header_t();

    // sets all header data
    header->setVersion(4);
    header->setHeaderLength(6);
    header->setTos(0);
    header->setTotalSize(sizeof(IPv4Header_t) + strlen(argv[5]) + 1);
    header->setIdentifier(0);
    header->setFlags(0);
    header->setFragmentOffset(0);
    header->setTTL(5);
    header->setProtocol(atoi(argv[2]));
    header->setSourceAddress(ipDecimalToBinary(std::string(argv[3])));
    header->setDestinationAddress(ipDecimalToBinary(std::string(argv[4])));
    header->setOptions(0);
    header->setHeaderChecksum();

    // creates socket
    int socket_info;
    struct sockaddr_in server;
    socket_info = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_info == -1) {
    printf("Could not create socket");
    }

    int enable = 1;
    if (setsockopt(socket_info, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0){
        perror("setsockopt(SO_REUSEADDR) failed");
        return 1;
    }
    server.sin_addr.s_addr = inet_addr( argv[1] );
    server.sin_family = AF_INET;
    server.sin_port = htons( atoi(argv[2]) );

    if (connect(socket_info, (struct sockaddr *)&server, sizeof(server)) <       0) 
    {
        perror("Connection error");
        return 1;
    }

    // allocates more memory to join together the header with the data
    size_t size = sizeof(IPv4Header_t) + strlen(argv[5]) + 1;
    char* message = new char[size];
    long i = 0;

    // copies header into packet
    for(char* c = (char*)header; c < (char*)header + sizeof(IPv4Header_t); c++)
        message[i++] = *c;

    // copies data into packet (argv[5] is the data)
    for(long st = 0; st <= strlen(argv[5]); st++)
    {
        message[i++] = argv[5][st];
    }
    
    // sends packet
    if(send(socket_info, message, size, 0) <0) 
    {        
        perror("Send failed");
        return 1;
    }
    std::cout << "Sent.\n";

    return 0;
}