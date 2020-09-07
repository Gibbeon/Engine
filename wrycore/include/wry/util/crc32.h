
/*

#include "sly/types.h"

#pragma once

// CRC-32C (iSCSI) polynomial in reversed bit order. 
#define POLY 0x82f63b78

// CRC-32 (Ethernet, ZIP, etc.) polynomial in reversed bit order. 
// #define POLY 0xedb88320 

// Generate CRC lookup table
template<unsigned c, int k = 8>
struct f : f<((c & 1) ? 0xedb88320 : 0) ^ (c >> 1), k - 1> { };
template<unsigned c>
struct f<c, 0> {
    enum { value = c };
};

constexpr u32 crc32c(u32 crc, const unsigned char* buf, size_t len) {
    crc = ~crc;
    while(len--) {
        crc ^= *buf++;
        for(int_t k = 0; k < 8; k++)
            crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
    }
    return ~crc;
}

static u32 dynamic_crc32(const char_t* str) {
    return crc32c(0, reinterpret_cast<const unsigned char*>(str), strlen(str));
}

static u32 dynamic_crc32_n(const char_t* str, size_t length) {
    return crc32c(0, reinterpret_cast<const unsigned char*>(str), length);
}

template<size_t L>
constexpr u32 static_crc32(const char_t (&str)[L]) {
    return crc32c(0, reinterpret_cast<const unsigned char*>(str), L - 1);
}

*/