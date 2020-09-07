#pragma once

#include "wry/global.h"
#include "wry/gfx/device.h"

namespace wry {
    namespace gfx {
        class Resource {
        public:
            Resource() = default;
            ~Resource() = default;

            template<typename T>
            retval_t<void> write(std::initializer_list<T> data);

            template<typename T>
            retval_t<void> write(const T* data, uint_t count);

            retval_t<void> write(const vptr_t data, uint_t size);
        };

        template<typename T>
        retval_t<void> write(std::initializer_list<T> data) {
            return write(data.begin(), data.end() - data.begin());
        }

        template<typename T>
        retval_t<void> write(const T* data, uint_t count) {
            return write(data, sizeof(T) * count);
        }
    } // namespace gfx
} // namespace wry


