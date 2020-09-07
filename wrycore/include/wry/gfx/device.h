#pragma once

#include "wry/global.h"
#include "wry/gfx/adapter.h"

namespace wry {
    namespace gfx {
        class Device {
        public:
            Device();
            Device(Adapter&);

            ~Device() = default;
        };
    } // namespace gfx
} // namespace wry