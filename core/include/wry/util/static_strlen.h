/*

#include "sly/types.h"

#pragma once

template<const char_t char_, const char_t* str_, uint_t value_ = 0>
struct static_strlen {
    static const unsigned int result = static_strlen<str_[value_], str_, value_ + 1>::result;
};

template<const char_t* str_, uint_t value_>
struct static_strlen<'\0', str_, value_> { static const unsigned int result = value_; };

*/