 #include "wry/global.h"

 uint_t test() {
     real_t value = 1.0f;
     wry::property_t<real_t> prop(value);

     prop = (real_t)2.0;

     return (uint_t)value;
 }