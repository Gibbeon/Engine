#pragma once

#include "wry/global.h"

namespace wry {
    namespace io {
        class Stream {
        public:
            Stream(vptr_t ptr) : _ptr((byte_t*)ptr), _pos(0) {

            }

            void read(vptr_t src, size_t size) {
                memcpy(src, &(_ptr[_pos]), size);
                _pos += size;
            }

            void write(vptr_t dest, size_t size) {
                memcpy(&(_ptr[_pos]), dest, size);
                _pos += size;
            }

            void reset() {
                _pos = 0;
            }

        private:
            size_t _pos;
            byte_t* _ptr;
        };
    }
}