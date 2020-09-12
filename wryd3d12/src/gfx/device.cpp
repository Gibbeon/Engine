#include "wry/gfx/device.h"
#include "wry/gfx/system.h"
#include "wry/d3d12/d3d12.h"

using namespace wry::gfx;

Device::Device() : Device(wry::gfx::System().defaultAdapter()) {

}

Device::Device(Adapter& adapter) : _adapter(adapter) {
    if (!SUCCEEDED(D3D12CreateDevice(reinterpret_cast<IDXGIAdapter1*>(adapter.handle()), D3D_FEATURE_LEVEL_11_0, IID_ID3D12Device, reinterpret_cast<vptr_t*>(&_handle))))
    {
        return; // error
    }
}

vptr_t Device::handle() const {
    return _handle;
} 

Adapter Device::adapter() const {
    return _adapter;
}  