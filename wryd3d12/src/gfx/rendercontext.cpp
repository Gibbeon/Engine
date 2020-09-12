#include "wry/gfx/rendercontext.h"
#include "wry/d3d12/d3d12.h"
#include "wry/d3d12/system.h"

using namespace wry::gfx;

namespace wry {
    namespace d3d12 {
        struct RenderContext {
            IDXGISwapChain3*            swapChain;
        };
    }
}

RenderContext::~RenderContext() {
    delete _handle;
}

RenderContext::RenderContext(Device& device, wry::os::Window& window): _device(device), _window(window) {
    auto context = new wry::d3d12::RenderContext();
    _handle = (vptr_t)context;

    wry::gfx::System system;
    auto d3d12Factory = reinterpret_cast<d3d12::System*>(system.handle())->factory;

    // ribe and create the swap chain.
    DXGI_SWAP_CHAIN_DESC1 swapChain = {};
    swapChain.BufferCount = 2; // how many buffers we will have, 2 allows us to have one actively being written to whilest the other is displayed
    swapChain.Width = 0;
    swapChain.Height = 0;
    swapChain.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // the color format for the buffer
    swapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // how this buffer is to be used
    swapChain.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // discard the buffer after it's displayed
    swapChain.SampleDesc.Count = 1; // for multisampling the image

    ThrowIfFailed(
        d3d12Factory->CreateSwapChainForHwnd(
        nullptr, //&_directCommandQueue.handle(),        // Swap chain needs the queue so that it can force a flush on it.
        (HWND)window.handle(),
        &swapChain,
        nullptr,
        nullptr,
        reinterpret_cast<IDXGISwapChain1**>(&context->swapChain)
        ));


    //size_t indicies[2];
    //_desctriptorTable.alloc(indicies, 2);

    // Create a RTV for each frame.
    //for (UINT n = 0; n < 2; n++)
    //{
    //    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
    //    rtvHandle.ptr = _desctriptorTable.getAt(indicies[n]);

    //    ID3D12Resource* ptr = nullptr;
    //    ThrowIfFailed(_swapChain->GetBuffer(n, IID_ID3D12Resource, reinterpret_cast<vptr_t*>(&ptr)));
    ///   getID3D12Device().CreateRenderTargetView(ptr, 0, rtvHandle); // writes the location of a render target view heap entry at the heap location
        
    //     _renderTargets[n].init(ptr, rtvHandle.ptr);
    //}    
}

vptr_t RenderContext::handle() const {
    return _handle;
}  

wry::retval_t<void> RenderContext::present() {
    auto swapChain = ((wry::d3d12::RenderContext*)_handle)->swapChain;
    if(FAILED(swapChain->Present(1, 0)))
    {
       HRESULT res = ((ID3D12Device*)_device.handle())->GetDeviceRemovedReason();
       ThrowIfFailed(res);
    }

    return success();
}

/*#include "sly/d3d12/gfx/rendercontext.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/d3d12/gfx/commandqueue.h"
#include "sly/win32/os/window.h"

using namespace sly::gfx;
D3D12RenderContextImpl::D3D12RenderContextImpl(D3D12DeviceImpl& device, sly::os::Win32Window& window) :
    _window(&window),
    _fence(device),
    _directCommandQueue(device),
    _desctriptorTable(device),
    _device(&device) {
}

sly::retval<void> D3D12RenderContextImpl::init(const RenderContextDesc& desc) {
    D3D12riptorTableBuilder descTableBuilder;

    descTableBuilder.setCapacity(2);
    
    _desctriptorTable.init(descTableBuilder.build());
    CommandQueueBuilder builder;
    _directCommandQueue.init(builder.build());
   
    // ribe and create the swap chain.
    DXGI_SWAP_CHAIN_DESC1 swapChain = {};
    swapChain.BufferCount = 2; // how many buffers we will have, 2 allows us to have one actively being written to whilest the other is displayed
    swapChain.Width = _window->getWidth();
    swapChain.Height = _window->getHeight();
    swapChain.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // the color format for the buffer
    swapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // how this buffer is to be used
    swapChain.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // discard the buffer after it's displayed
    swapChain.SampleDesc.Count = 1; // for multisampling the image

    ThrowIfFailed(reinterpret_cast<D3D12DeviceImpl*>(&getDevice())->getIDXGIFactory4().CreateSwapChainForHwnd(
        &_directCommandQueue.getID3D12CommandQueue(),        // Swap chain needs the queue so that it can force a flush on it.
        _window->getHwnd(),
        &swapChain,
        nullptr,
        nullptr,
        reinterpret_cast<IDXGISwapChain1**>(&_swapChain)
        ));

    // This sample does not support fullscreen transitions.
    //ThrowIfFailed(factory->MakeWindowAssociation(Win32Application::GetHwnd(), DXGI_MWANO_ALT_ENTER));

    _drawFrameIndex = _swapChain->GetCurrentBackBufferIndex();

    size_t indicies[2];
    _desctriptorTable.alloc(indicies, 2);

    // Create a RTV for each frame.
    for (UINT n = 0; n < 2; n++)
    {
        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
        rtvHandle.ptr = _desctriptorTable.getAt(indicies[n]);

        ID3D12Resource* ptr = nullptr;
        ThrowIfFailed(_swapChain->GetBuffer(n, IID_ID3D12Resource, reinterpret_cast<vptr_t*>(&ptr)));
        getID3D12Device().CreateRenderTargetView(ptr, 0, rtvHandle); // writes the location of a render target view heap entry at the heap location
        
            _renderTargets[n].init(ptr, rtvHandle.ptr);
    }    

    return success();
}

sly::retval<void> D3D12RenderContextImpl::release() {
    
    _renderTargets[0].release();
    _renderTargets[1].release();
    
    _swapChain->Release();
    _fence.release();

    _desctriptorTable.release();
    _directCommandQueue.release();

    return success();
}

void  D3D12RenderContextImpl::update()
{
    _window->processMessages();
}

void D3D12RenderContextImpl::setVisible(bool_t show)
{
    _window->setVisible(show);
}

void D3D12RenderContextImpl::present()
{
    // Present the frame.
    if(FAILED(_swapChain->Present(1, 0)))
    {
       HRESULT res = getID3D12Device().GetDeviceRemovedReason();
       ThrowIfFailed(res);
    }

    // Wait for the command list to execute; we are reusing the same command 
    // list in our main loop but for now, we just want to wait for setup to 
    // complete before continuing. Not ideal!

    // Signal and increment the fence value.
    // if the command queue didn't do anything this will hang!!!
    //fence_.waitFor(directCommandQueue.getID3D12CommandQueue());

    _drawFrameIndex = _swapChain->GetCurrentBackBufferIndex();
}

*/