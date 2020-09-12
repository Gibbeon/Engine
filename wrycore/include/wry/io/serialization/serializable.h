#pragma once

#include "wry/global.h"

namespace wry {
    namespace io {
        class ISerializable {
        public:
            ISerializable() {}

            template <typename Archive>
            ISerializable(Archive&) {}

            template <typename Archive>
            bool_t serialize(Archive&) { return false; }
        };
    }
}