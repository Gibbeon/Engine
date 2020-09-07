#pragma once

#include "wry/global.h"

namespace wry {
    namespace os {
        class Window {
        public:
            Window();
            virtual ~Window();

            int_t left()    const;
            int_t top()     const;
            uint_t width()  const;
            uint_t height() const;
            gsl::czstring title() const;

            Window& left(int_t left);
            Window& top(int_t top);
            Window& width(uint_t width);
            Window& height(uint_t height);
            Window& title(gsl::czstring title);

            retval_t<void> update();
        };
    }
}