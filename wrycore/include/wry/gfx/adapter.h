#pragma once

#include "wry/global.h"

namespace wry {
    namespace gfx {
        class Adapter {
        public:
            Adapter(vptr_t handle);
            ~Adapter() = default;

            vptr_t handle() const;  

        private:
            vptr_t _handle;
        };
    } // namespace gfx
} // namespace wry