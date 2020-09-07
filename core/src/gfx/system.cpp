#include "wry/gfx/system.h"
using namespace wry::gfx;

static Adapter* _defaultAdapter = nullptr;
static std::vector<Adapter> _adapters;

gsl::span<Adapter> System::adapters() const {
    static bool_t initialized = false;
    if(!initialized) {
        //adapters.push_back();
        initialized = true;
    }

    return _adapters;
}

Adapter& System::adapter() const {
    return *_defaultAdapter;
}

System& System::adapter(Adapter& adapter) {
    _defaultAdapter = &adapter;

    return *this;
}