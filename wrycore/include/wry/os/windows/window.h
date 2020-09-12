#pragma once

#include "wry/global.h"

namespace wry {
    namespace os {
        class Window {
        public:
            Window();
            Window(vptr_t handle);

            virtual ~Window();

            int_t  left()    const;
            int_t  top()     const;
            uint_t width()   const;
            uint_t height()  const;
            bool_t visible()  const;
            gsl::czstring title() const;
            vptr_t handle() const;

            Window& left(int_t left);
            Window& top(int_t top);
            Window& width(uint_t width);
            Window& height(uint_t height);
            Window& title(gsl::czstring title);
            Window& visible(bool_t visible);

            retval_t<void> update();

        private:
            retval_t<void> create();
            vptr_t         _handle;
        };
    }
}