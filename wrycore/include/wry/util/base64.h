#pragma once

/*

#include "sly/global.h"

namespace sly {
    class Base64 {
    public:
        inline size_t requiredEncodeBufferSize(size_t length) {
            return ((length / 3) + (length % 3 > 0)) * 4;
        }

        inline size_t requiredDecodeBufferSize(size_t length) {
            return (length * 4) / 3;
        }

        inline static const char kEncodeLookup[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        inline static const char kPadCharacter   = '=';

        inline retval<void> encode(const gsl::span<byte_t>& input, char_t* dest, size_t size)   //const std::vector<byte_t>& input)
        {
            std::uint32_t temp {};
            auto          it       = input.begin();
            auto          dest_ptr = dest;

            for(std::ptrdiff_t i = 0; i < input.size() / 3; ++i) {
                temp = (*it++) << 16;
                temp += (*it++) << 8;
                temp += (*it++);
                *(dest_ptr++) = kEncodeLookup[(temp & 0x00FC0000) >> 18];
                *(dest_ptr++) = kEncodeLookup[(temp & 0x0003F000) >> 12];
                *(dest_ptr++) = kEncodeLookup[(temp & 0x00000FC0) >> 6];
                *(dest_ptr++) = kEncodeLookup[(temp & 0x0000003F)];
            }

            switch(input.size() % 3) {
                case 1:
                    temp          = (*it++) << 16;
                    *(dest_ptr++) = kEncodeLookup[(temp & 0x00FC0000) >> 18];
                    *(dest_ptr++) = kEncodeLookup[(temp & 0x0003F000) >> 12];
                    *(dest_ptr++) = kPadCharacter;
                    *(dest_ptr++) = kPadCharacter;
                    break;
                case 2:
                    temp = (*it++) << 16;
                    temp += (*it++) << 8;
                    *(dest_ptr++) = kEncodeLookup[(temp & 0x00FC0000) >> 18];
                    *(dest_ptr++) = kEncodeLookup[(temp & 0x0003F000) >> 12];
                    *(dest_ptr++) = kEncodeLookup[(temp & 0x00000FC0) >> 6];
                    *(dest_ptr++) = kPadCharacter;
                    break;
            }

            return success();
        }

        retval<size_t> decode(gsl::czstring<> input, size_t length, char_t* dest, size_t size) {
            Expects(length % 4);

            size_t padding {};

            if(length) {
                if(input[length - 1] == kPadCharacter)
                    padding++;
                if(input[length - 2] == kPadCharacter)
                    padding++;
            } else {
                return 0;
            }

            Expects(size >= (requiredDecodeBufferSize(length) - padding));

            //std::vector<byte> decoded;
            //decoded.reserve(requiredDecodeBufferSize(length) - padding);

            std::uint32_t temp {};
            auto          it       = input;
            auto          dest_ptr = dest;

            while(it < (input + length)) {
                for(std::size_t i = 0; i < 4; ++i) {
                    temp <<= 6;
                    if(*it >= 0x41 && *it <= 0x5A)
                        temp |= *it - 0x41;
                    else if(*it >= 0x61 && *it <= 0x7A)
                        temp |= *it - 0x47;
                    else if(*it >= 0x30 && *it <= 0x39)
                        temp |= *it + 0x04;
                    else if(*it == 0x2B)
                        temp |= 0x3E;
                    else if(*it == 0x2F)
                        temp |= 0x3F;
                    else if(*it == kPadCharacter) {
                        switch((input + length) - it) {
                            case 1:
                                *(dest_ptr++) = ((temp >> 16) & 0x000000FF);
                                *(dest_ptr++) = ((temp >> 8) & 0x000000FF);
                                return (size_t)(dest_ptr - dest);
                            case 2:
                                *(dest_ptr++) = ((temp >> 10) & 0x000000FF);
                                return (size_t)(dest_ptr - dest);
                            default:
                                throw std::runtime_error("Invalid padding in base64!");
                        }
                    } else
                        throw std::runtime_error("Invalid character in base64!");

                    ++it;
                }

                *(dest_ptr++) = ((temp >> 16) & 0x000000FF);
                *(dest_ptr++) = ((temp >> 8) & 0x000000FF);
                *(dest_ptr++) = ((temp)&0x000000FF);
            }

            return (size_t)(dest_ptr - dest);
        }
    };
}   // namespace sly

*/
