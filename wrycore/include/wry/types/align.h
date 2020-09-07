#pragma once

#include "wry/global.h"

template<uint_t align_to = 16, typename TType = uint_t> 
TType align(TType value_)
{
    return (value_ + (align_to - 1)) & ~(align_to - 1);
};

