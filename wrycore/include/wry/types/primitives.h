#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <limits.h>

#if defined(_WIN32)
    #include <tchar.h>
#else
    #if UNICODE 
    typedef wchar_t char_t;
    #else
    typedef char char_t;
    #endif
#endif

typedef unsigned long long u64;
typedef signed long long s64;

typedef unsigned int u32;
typedef signed int s32;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned char u8;
typedef signed char s8;

typedef float f32;
typedef double f64;
typedef long double f80;

typedef bool bool_t;
typedef f32 real_t;
typedef char char_t;
typedef u8 byte_t;
typedef s16 short_t;
typedef s32 int_t;
typedef s64 long_t;
typedef u32 ushort_t;
typedef u32 uint_t;
typedef u64 ulong_t;
typedef void* vptr_t;

#if !defined(_SIZE_T)
    #if defined(_WIN64)
        typedef unsigned long long size_t;
    #else    
        typedef unsigned int size_t;
    #endif
#endif

#ifdef FALSE
#undef FALSE
#endif
#ifdef TRUE
#undef TRUE
#endif
#ifdef NULL
#undef NULL
#endif 

#ifndef _WIN32
#define INFINITE ((u32)-1)
#endif

#define FALSE false
#define TRUE true
#define NULL nullptr
