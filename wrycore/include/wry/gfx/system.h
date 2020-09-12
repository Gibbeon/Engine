#pragma once

#include "wry/global.h"
#include "wry/gfx/adapter.h"

namespace wry {
    namespace gfx {
        class System {
        public:
            System();
            ~System() = default;

            gsl::span<Adapter> adapters();
            Adapter& defaultAdapter() const;

            System& defaultAdapter(Adapter& adapter);

            vptr_t handle() const;            
        private:
            vptr_t      _handle;
        };
    } // namespace gfx
} // namespace wry