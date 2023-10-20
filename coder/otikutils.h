#pragma once
#include <cstdint>

unsigned char* int2lendian(uint32_t);
unsigned char* sint2lendian(uint16_t);
uint32_t lendian2int(unsigned char*);
uint16_t lendian2sint(unsigned char*);
