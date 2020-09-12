#include "wry/os/windows/window.h"
#include "wry/win32/win32.h"

using namespace wry::os;
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

Window::Window() {
    create();
}

Window::Window(vptr_t handle) {

}

Window::~Window() {

}


vptr_t Window::handle() const {
    return _handle;
}

Window& Window::width(uint_t width) {
    RECT rect;
    GetWindowRect((HWND)_handle, &rect);
    SetWindowPos((HWND)_handle, nullptr, 0, 0, width, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOMOVE );
    return *this;
}

Window& Window::height(uint_t height) {
    RECT rect;
    GetWindowRect((HWND)_handle, &rect);
    SetWindowPos((HWND)_handle, nullptr, 0, 0, rect.right - rect.left, height, SWP_NOZORDER | SWP_NOMOVE );
    return *this;
}

Window& Window::title(gsl::czstring title) {
    SetWindowTextA((HWND)_handle, title);
    return *this;
}

Window& Window::visible(bool_t visible) {
    ShowWindow((HWND)_handle, visible ? SW_SHOWDEFAULT : SW_HIDE);
    return *this;
}


wry::retval_t<void> Window::update()
{
    MSG msg = {};
    bool_t process = true;
    while (process)
    {
        process = false;
        // Process any messages in the queue.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            process = true; 
        }
    }

    // Return this part of the WM_QUIT message to Windows.
    return static_cast<char>(msg.wParam);
}

wry::retval_t<void> Window::create() {
    HINSTANCE hInstance= GetModuleHandle(NULL);
    
    // Initialize the window class.
    WNDCLASSEX windowClass = { 0 }; 
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName =  "Win32Window";
    RegisterClassEx(&windowClass);

    ::RECT windowRect = { 0, 0, static_cast<LONG>(640), static_cast<LONG>(480) };
    AdjustWindowRect(&windowRect, WS_OVERLAPPED, FALSE);
    
    // Create the window and store a handle to it.
    _handle = CreateWindowEx(
        WS_EX_TRANSPARENT,
        windowClass.lpszClassName,
        "",
        WS_OVERLAPPED,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr,        // We have no parent window.
        nullptr,        // We aren't using menus.
        hInstance,
        this);

    return success();
}

// Main message handler for the sample.
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //Win32Window* pSample = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch (message)
    {
        case WM_CREATE:
        {
            // Save the DXSample* passed in to CreateWindow.
            LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
        }
        return 0;

        case WM_PAINT: {
            ValidateRect(hWnd, NULL);
        } return 0;

        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
    }

    // Handle any messages the switch statement didn't.
    return DefWindowProc(hWnd, message, wParam, lParam);
}