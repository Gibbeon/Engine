#include "wry/gfx/system.h"
#include "wry/d3d12/d3d12.h"

using namespace wry::gfx;

//struct D3D12Adapter {
//    IDXGIAdapter1*      adapter     = nullptr;
//};

Adapter::Adapter(vptr_t handle) {
    _handle = handle;

    //DXGI_ADAPTER_DESC1 desc;
    //adapter->GetDesc1(&desc);    
}

vptr_t Adapter::handle() const {
    return _handle;
}  