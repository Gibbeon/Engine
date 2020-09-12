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
            
            vptr_t      handle() const;   
            Adapter     adapter() const;   
                     
        private:
            vptr_t      _handle;
            Adapter&    _adapter;
        };
    } // namespace gfx
} // namespace wry