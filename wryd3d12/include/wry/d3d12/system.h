#include "wry/gfx/system.h"
#include "wry/gfx/adapter.h"
#include "wry/d3d12/d3d12.h"

namespace wry {
    namespace d3d12 {
        struct System {
            bool_t              initialized = false;
            IDXGIFactory4*      factory     = nullptr;
            ID3D12Debug*        debugTask   = nullptr;
            
            gfx::Adapter*                defaultAdapter   = nullptr;
            std::vector<gfx::Adapter>    adapters;
        };
    }
}


