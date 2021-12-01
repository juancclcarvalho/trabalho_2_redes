#include "utils.hpp"
// extracts n bits from source, shifts value by offset before doing so
uint32_t extractSubsequence(int offset, int n, uint32_t& source)
{
    uint32_t mask = 0;

    for(int i = 0; i < n; i++)
    {
        mask = mask << 1;
        mask += 1;
    }
    mask = mask << offset;

    return ((source & mask) >> offset);
}
// inserts value into source, shifts value by offset before doing so
void insertSubsequence(int offset, uint32_t& source, uint32_t value)
{
    value = value << offset;
    source |= value;
}
// checks if given ip is a valid one
bool isValidIp(std::string ip)
{
    int current = 0;
    uint32_t n = 0;
    for(auto& c : ip)
    {
        if(c == '.')
        {
            n++;
            if(n == 4) return false;
            if(current > 255) return false;
            current = 0;
        }
        else if(isdigit(c))
        {
            current *=10;
            current += c - '0';
        }
        else return false;
    }

    return current <= 255 ? true : false;
}
// converts an ip from a string/decimal representation to a 32 bit integer
uint32_t ipDecimalToBinary(std::string ip)
{
    int current = 0;
    uint32_t n = 0;
    uint32_t output = 0;
    for(auto& c : ip)
    {
        if(c == '.')
        {
            n++;
            insertSubsequence(32 - (n * 8), output, current);
            current = 0;
        }
        else
        {
            current *= 10;
            current += c - '0';
        }
    }
    insertSubsequence(0, output, current);
    return output;
}

std::string ipBinaryToDecimal(uint32_t ip)
{
    std::string byte[4];
    int buffer;
    int power;

    for(int i = 0; i < 32; i++)
    {
        if(i % 8 == 0)
        {
            if(i != 0)
                byte[(i/8) - 1] = std::string(itoa(buffer));
            buffer = 0;
            power = 1;
        }
        if((ip & (1 << i)) != 0)
            buffer += power;
        power = power << 1;
    }

    byte[3] = std::string(itoa(buffer));
    std::string output = "";
    for(int i = 3; i >= 0; i--)
    {
        output += byte[i];
        if(i != 0)
            output += ".";
    }

    return output;
}

char* itoa(int num)
{
    char* buffer = new char[4];
    snprintf(buffer, sizeof(buffer), "%d", num);
    return buffer;
}