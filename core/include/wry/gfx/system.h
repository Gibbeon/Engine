#pragma once

#include "wry/global.h"
#include "wry/gfx/adapter.h"

namespace wry {
    namespace gfx {
        class System {
        public:
            System() = default;
            ~System() = default;

            gsl::span<Adapter> adapters() const;
            Adapter& adapter() const;

            System& adapter(Adapter& adapter);
        };
    } // namespace gfx
} // namespace wry