/*

#include "sly/types.h"

#pragma once

template<uint_t value_>
struct static_log2 {
    static const uint_t result = static_log2<value_ / 2>::result + 1;
};

template<>
struct static_log2<1> { static const uint_t result = 0; };

template<>
struct static_log2<0> { };

*/