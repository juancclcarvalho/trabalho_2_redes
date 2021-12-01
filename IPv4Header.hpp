#include <iostream>
#include "utils.hpp"

class IPv4Header_t
{
    private:
      uint32_t firstLine;  // VERSION | HEADER LENGHTH | Tos | TOTAL LENGTH
      uint32_t secondLine;// IDENTIFIER | FLAGS | FRAGMENT OFFSET
      uint32_t thirdLine;// TTL | PROTOCOL | HEADER CHECKSUM
      uint32_t sourceAddress;
      uint32_t destinationAddress;
      uint32_t options;
    
    public:
    void setVersion(int number);
    void setHeaderLength(int length);
    void setTos(int serviceType);
    void setTotalSize(int size);
    void setIdentifier(int identifier);
    void setFlags(int flag);
    void setFragmentOffset(int fragmentOffset);
    void setTTL(int TTL);
    void setProtocol(int protocol);
    void setSourceAddress(uint32_t ip);
    void setDestinationAddress(uint32_t ip);
    void setOptions(uint32_t options);
    void setHeaderChecksum();

    int getVersion();
    int getHeaderLength();
    int getTos();
    int getIdentifier();
    int getFlags();
    int getFragmentOffset();
    int getTTL();
    int getProtocol();
    uint32_t getSourceAddress();
    uint32_t getDestinationAddress();
    uint32_t getOptions();
    int getHeaderChecksum();
};