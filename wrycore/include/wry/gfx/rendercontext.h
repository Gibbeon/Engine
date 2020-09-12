#pragma once

#include "wry/global.h"
#include "wry/gfx/device.h"
#include "wry/os/windows/window.h"

namespace wry {
    namespace gfx {
        class RenderContext {
        public:
            RenderContext(Device& device, os::Window& window);
            ~RenderContext();
            
            vptr_t handle() const;  
            retval_t<void> present();          
        private:
            vptr_t          _handle;
            Device&         _device;
            os::Window&     _window;

            //Fence           _fence;
            //CommandQueue    _directCommandQueue;
            //DescriptorTable _desctriptorTable;
            //RenderTarget    _renderTargets[2];
        };
    } // namespace gfx
} // namespace wry