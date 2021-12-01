#include <iostream>
#include <string.h>

uint32_t extractSubsequence(int offset, int n, uint32_t& source);
void insertSubsequence(int offset, uint32_t& source, uint32_t value);
bool isValidIp(std::string ip);
uint32_t ipDecimalToBinary(std::string ip);
std::string ipBinaryToDecimal(uint32_t ip);
char* itoa(int num);