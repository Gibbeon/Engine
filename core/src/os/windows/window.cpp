#include "wry/os/windows/window.h"
using namespace wry::os;

Window::Window() {

}

Window::~Window() {

}

Window& Window::width(uint_t width) {
    return *this;
}

Window& Window::height(uint_t height) {
    return *this;
}

Window& Window::title(gsl::czstring title) {
    return *this;
}