#include "routing_table.hpp"
#include <algorithm>

routing_entry_t::routing_entry_t(const char* s, bool* success)
{
    std::string input = s;
    std::string split_string[4];
    int size = input.length();
    int start = 0;
    for(int i = 0; i < 4; i++)
    {
        int end = input.find("/", start);
        if(end == std::string::npos and i != 3)
        {
            std::cout<< '"' << input << '"' << " <---------- INVALID FORMAT\n";
            *success = false;
            return;
        }
        split_string[i] = input.substr(start, (end - start));
        start = end + 1;
        //std::cout << split_string[i] << '\n';
    }

    for(int i = 0 ; i < 3; i++)
    {
        if(!isValidIp(split_string[i]))
        {
            std::cout << '"' << split_string[i] << '"' << " is not a valid ip address\n";
            *success = false;
            return;
        }
    }
    
    destination = ipDecimalToBinary(split_string[0]);
    mask = ipDecimalToBinary(split_string[1]);
    gateway = ipDecimalToBinary(split_string[2]);
    interface = (uint32_t)std::atoi(split_string[3].c_str());
    *success = true;
}

bool operator<(const routing_entry_t&a, const routing_entry_t& b)
{
    return a.mask < b.mask;
}

routing_table_t::routing_table_t(int argc, char const *argv[])
{
    routing_entry_t* newEntry;
    bool* success = new bool;

    for(int i = 2; i < argc; i++)
    {
        newEntry = new routing_entry_t(argv[i], success);
        if(success) table.push_back(*newEntry);
    }

    // sorts table based off the entries' masks
    std::sort(table.begin(), table.end());
}

bool routing_table_t::choose_route(uint32_t destinationAddress, uint32_t* ip, uint32_t* port)
{
    for(auto& entry : table)
    {
        if((entry.destination & entry.mask) == (destinationAddress & entry.mask) )
        {
            *ip = entry.gateway;
            *port = entry.interface; 
            return true;
        }
    }

    return false;
}