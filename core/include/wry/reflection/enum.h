#pragma once

/*

#include <cstddef>
#include <string>

#include "sly/runtime/typeinfo.h"

#define ENUM_PARSE(EnumName, ...)                                                                                                                                                                                                         \
    namespace {                                                                                                                                                                                                                           \
        bool_t EnumName##_initialized = ::sly::Enum<EnumName>::init<IDENTITY(COUNT(__VA_ARGS__)), STRING_LEN(__VA_ARGS__)>(IDENTITY(COUNT(__VA_ARGS__)), { IDENTITY(STRINGIZE(__VA_ARGS__)) }, { IDENTITY(IGNORE_ASSIGN(__VA_ARGS__)) }); \
    }

#define ENUM_DECL(EnumName, ...) \
    typedef enum {               \
        __VA_ARGS__              \
    } EnumName;                  \
    ENUM_PARSE(EnumName, __VA_ARGS__);

#define ENUM_DECL_OFTYPE(EnumName, Type, ...) \
    typedef enum : Type {                     \
        __VA_ARGS__                           \
    } EnumName;                               \
    ENUM_PARSE(EnumName, __VA_ARGS__);

#define IGNORE_ASSIGN_SINGLE(expression) (ignore_assign) expression,
#define IGNORE_ASSIGN(...)               IDENTITY(MAP(IGNORE_ASSIGN_SINGLE, __VA_ARGS__))

#define STRINGIZE_SINGLE(expression) #expression,
#define STRINGIZE(...)               IDENTITY(MAP(STRINGIZE_SINGLE, __VA_ARGS__))

namespace sly {

    template<typename T>
    struct Enum {
    public:
        using underlying_type = __underlying_type(T);
        using type            = T;

        static retval<const TypeInfo&> getType();

        static retval<const char_t*> toString(T value);
        static retval<const T>       parse(const char_t* name);

        template<size_t N, size_t NSize>
        static retval<bool_t> init(size_t count, const char_t* const (&raw_names)[N], const s32 (&values)[N]);

        static size_t             count();
        static gsl::span<s32>     values();
        static gsl::span<u32>     hashes();
        static gsl::span<char_t*> names();

    protected:
        static size_t   _count;
        static s32*     _values;
        static u32*     _hashes;
        static char_t** _names;
    };

    template<typename T>
    size_t Enum<T>::count() {
        return _count;
    }

    template<typename T>
    gsl::span<s32> Enum<T>::values() {
        return gsl::make_span(_values, _count);
    }

    template<typename T>
    gsl::span<u32> Enum<T>::hashes() {
        return gsl::make_span(_hashes, _count);
    }

    template<typename T>
    gsl::span<char_t*> Enum<T>::names() {
        return gsl::make_span(_names, _count);
    }

    template<typename T>
    retval<const TypeInfo&> getType() {
        static const TypeInfo instance = TypeInfo::get<T>();
        return reference(instance);
    }

    template<typename T>
    retval<const char_t*> Enum<T>::toString(T value) {
        for(size_t index = 0; index < count(); ++index) {
            if(values()[index] == value)
                return names()[index];
        }

        static const StatusCode SLY_NOTFOUND = 0x02;

        return failed<const char_t*>((StatusCode)SLY_NOTFOUND, "The value could not be parsed into an Enum name");
    }

    template<typename T>
    retval<const T> Enum<T>::parse(const char_t* name) {
        bool_t started   = false;
        size_t start_pos = 0;
        size_t str_len   = strlen(name);
        u32    result    = 0;

        for(size_t n = 0; n < str_len + 1; n++) {
            constexpr const char_t delims[] = ",|\t\n\v\f\r ";

            if(started == false) {
                started = __iscsym(name[n]);
                if(started) {
                    start_pos = n;
                }
            } else {
                if(!(started = __iscsym(name[n]))) {
                    u32 hash = dynamic_crc32_n(&(name[start_pos]),
                                               n - start_pos);
                    for(size_t index = 0; index < count(); ++index) {
                        if(hashes()[index] == hash) {
                            result |= values()[index];
                        }
                    }
                }
            }
        }
        return (T)result;
    }

    template<size_t N>
    static constexpr size_t sizeof_r(const char_t* const (&raw_names)[N], size_t index = N) {
        index--;
        return strlen(raw_names[index]) + sizeof_r(raw_names, index);
    }

    template<typename T>
    template<size_t N, size_t NSize>
    retval<bool_t> Enum<T>::init(size_t count, const char_t* const (&raw_names)[N], const s32 (&values)[N]) {
        static char_t* nameary_buffer[N];
        static char_t  names_buffer[(NSize + 1)];
        static u32     hashes_buffer[N];
        static s32     values_buffer[N];
        static bool_t  initialized = false;

        if(!initialized) {
            char_t* ptr_names = names_buffer;

            _names  = nameary_buffer;
            _hashes = hashes_buffer;
            _values = values_buffer;
            _count  = count;

            for(size_t index = 0; index < _count; ++index) {
                _values[index] = values[index];
                size_t length  = std::strcspn(raw_names[index], " =\t\n\r") + 1;

                _names[index] = ptr_names;
                ptr_names += (length + 1);

                ::strncpy_s(_names[index], length, raw_names[index], _TRUNCATE);

                _names[index][length] = '\0';

                _hashes[index] = dynamic_crc32(_names[index]);
            }
            initialized = true;
            return true;
        }
        return true;
    }

    template<typename T>
    size_t Enum<T>::_count;

    template<typename T>
    s32* Enum<T>::_values;

    template<typename T>
    u32* Enum<T>::_hashes;

    template<typename T>
    char_t** Enum<T>::_names;

}   // namespace sly

*/