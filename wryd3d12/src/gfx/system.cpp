#include "wry/d3d12/system.h"
#include "wry/d3d12/d3d12.h"

using namespace wry::gfx;

static wry::d3d12::System d3d12System;

System::System() {
    _handle = &d3d12System;

    if(d3d12System.initialized)
        return;
        
    UINT dxgiFactoryFlags = 0;
#ifdef DEBUG
    {
        if (SUCCEEDED(D3D12GetDebugInterface(IID_ID3D12Debug, reinterpret_cast<vptr_t*>(&d3d12System.debugTask)))) {
            d3d12System.debugTask->EnableDebugLayer();

            // Enable additional debug layers.
            dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
        }
    }
#endif

    if (SUCCEEDED(CreateDXGIFactory2(dxgiFactoryFlags, IID_IDXGIFactory4, reinterpret_cast<vptr_t*>(&d3d12System.factory)))) {
        IDXGIAdapter1*      adapter     = nullptr;
        for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != d3d12System.factory->EnumAdapters1(adapterIndex, &adapter); ++adapterIndex) {
            d3d12System.adapters.push_back(Adapter(adapter));
        }

        if (SUCCEEDED( d3d12System.factory->EnumWarpAdapter(IID_IDXGIAdapter1, reinterpret_cast<vptr_t*>(&adapter)))) {
            d3d12System.adapters.push_back(Adapter(adapter));
        } else {
            //error
        }
        d3d12System.defaultAdapter = &d3d12System.adapters[0];
    } else {
        //error
    }

    d3d12System.initialized = true;
}

gsl::span<Adapter> System::adapters() {
    return d3d12System.adapters;
}

Adapter& System::defaultAdapter() const {
    return *d3d12System.defaultAdapter;
}

System& System::defaultAdapter(Adapter& adapter) {
    d3d12System.defaultAdapter = &adapter;
    return *this;
}

vptr_t System::handle() const {
    return _handle;
}  