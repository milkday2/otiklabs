#pragma once
#include <cstdint>

typedef struct kamd_header {
    unsigned char signature[4] = {'\x4b','\x61','\x4d','\x64'};
    unsigned char version[2] = { '\x01','\x00' };
    unsigned char comp_method[2] = { '\x00','\x00' };
    unsigned char intf_protection[2] = { '\x00','\x00' };
    uint32_t file_size = 0;
    uint16_t filename_size = 0;
    uint16_t c_overhead_size = 0;
    uint16_t i_overhead_size = 0;
}kamd_header;
