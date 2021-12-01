#include <iostream>
#include "IPv4Header.hpp"
#include <vector>

class routing_entry_t
{
    public:
    uint32_t destination;
    uint32_t mask;
    uint32_t gateway;
    uint32_t interface;

    
    routing_entry_t(const char* s, bool* success);
};

class routing_table_t
{
    public:
    std::vector<routing_entry_t> table;
    routing_table_t(int argc, char const *argv[]);
    bool choose_route(uint32_t destinationAddress, uint32_t* ip, uint32_t* port);
};