#include "IPv4Header.hpp"

void IPv4Header_t::setVersion(int number){
    insertSubsequence(28, firstLine, number);
}

void IPv4Header_t::setHeaderLength(int length){
    insertSubsequence(24, firstLine, length);
}

void IPv4Header_t::setTos(int serviceType){
    insertSubsequence(16, firstLine, serviceType);
}

void IPv4Header_t::setTotalSize(int size){
    insertSubsequence(0, firstLine, size);
}

void IPv4Header_t::setIdentifier(int identifier)
{

}

void IPv4Header_t::setFlags(int flag)
{

}

void IPv4Header_t::setFragmentOffset(int fragmentOffset)
{

}

void IPv4Header_t::setTTL(int TTL){
    insertSubsequence(24, thirdLine, TTL);
}

void IPv4Header_t::setProtocol(int TTL)
{

}

void IPv4Header_t::setSourceAddress(uint32_t ip){
    sourceAddress = ip;
}

void IPv4Header_t::setDestinationAddress(uint32_t ip){
    destinationAddress = ip;
}

void IPv4Header_t::setOptions(uint32_t options)
{

}

void IPv4Header_t::setHeaderChecksum()
{

}

int IPv4Header_t::getVersion()
{
    return 0;
}

int IPv4Header_t::getHeaderLength()
{
    return 0;
}

int IPv4Header_t::getTos()
{
    return 0;
}

int IPv4Header_t::getIdentifier()
{
    return 0;
}

int IPv4Header_t::getFlags()
{
    return 0;
}

int IPv4Header_t::getFragmentOffset()
{
    return 0;
}

int IPv4Header_t::getTTL()
{
    uint32_t output = extractSubsequence(24,8, thirdLine);
    return (int) output;
}

int IPv4Header_t::getProtocol()
{
    return 0;
}

uint32_t IPv4Header_t::getSourceAddress(){
    return sourceAddress;
}

uint32_t IPv4Header_t::getDestinationAddress(){
   return destinationAddress;
}

uint32_t IPv4Header_t::getOptions(){
    return options;
}

int IPv4Header_t::getHeaderChecksum()
{
    return 0;
}
