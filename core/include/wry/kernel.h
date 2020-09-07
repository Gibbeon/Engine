#pragma once
/*

#include "wry/global.h"

namespace wry {
  
    class IKernel {
    public:         
        virtual ~IKernel () {}

        //virtual IMemorySystem&              memory()        const = 0;

        //virtual os::IFileSystem&            filesystem()    const = 0;
        //virtual os::IOperatingSystem&       system()        const = 0;
        //virtual os::IWindowSystem&          windows()       const = 0;
        //virtual gfx::IRenderSystem&         graphics()     const = 0;
        
        //IConfiguration&      config();
        //IProfiler&           profiler();
        //IDebugger&           debugger();
        //ILog&                logger();
        //INetworkSystem&      net();

    protected:
        virtual retval<void> init() = 0;
        virtual retval<void> release() = 0;

        IKernel() {}
    };

    class Kernel : public IKernel {
    public:        
        static Kernel& get();
        virtual ~Kernel();
        
        Kernel( Kernel const& )              = delete;
        Kernel( Kernel && )                  = delete;
        Kernel& operator = ( Kernel const& ) = delete;
        Kernel& operator = ( Kernel && )     = delete;

        //virtual IMemorySystem&              memory()        const;

        //virtual os::IFileSystem&            filesystem()    const;
        //virtual os::IOperatingSystem&       system()        const;
        //virtual os::IWindowSystem&          windows()       const;
        //virtual gfx::IRenderSystem&         graphics()      const;
        
        //IConfiguration&      config();
        //IProfiler&           profiler();
        //IDebugger&           debugger();
        //ILog&                logger();
        //INetworkSystem&      net();

    protected:        
        Kernel() {}

        virtual retval<void> init();
        virtual retval<void> release();

    private:
        bool_t _initialized;

    };
}
*/