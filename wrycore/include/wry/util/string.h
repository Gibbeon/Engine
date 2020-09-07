/*

#include <typeinfo>
#include "sly/types.h"

static char_t* ltrim(char_t* str) {
    while(*str && isspace(*str++)) { }
    return str;
}

static char_t* rtrim(char_t* str) {
    char_t* buffer = str;
    while(*str++)
        ;   // move to end of string
    size_t end = str - buffer - 1;
    while(end > 0 && isspace(buffer[end - 1]))
        --end;         // backup over trailing spaces
    buffer[end] = 0;   // remove trailing spaces
    return str;
}

static char_t* trim(char_t* str) {
    return ltrim(rtrim(str));
}

*/
