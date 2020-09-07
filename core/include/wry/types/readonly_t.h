#pragma once

#include <type_traits>
#include "wry/types/traits.h"

namespace wry {
    template <typename T, typename = typename std::is_reference<T>::type>
    struct readonly_t { };

    template <typename T>
    struct readonly_t<T, std::false_type> { 
    public:
    
        using type = T;
        using type_pointer = typename std::remove_reference<T>::type*;
        using type_reference = typename std::remove_reference<T>::type&;

        readonly_t(type_reference value) : 
            _value(value) {}
        
        ~readonly_t() = default;
        readonly_t& operator =(const readonly_t&) = delete;

        template <class V, typename Y = T, typename std::enable_if_t<is_unique_ptr<Y>::value || is_shared_ptr<Y>::value>* = nullptr>
        V to() const {
            return reinterpret_cast<V>(_value.get());
        }

        template <class V, typename Y = T, typename std::enable_if_t<!is_unique_ptr<Y>::value && !is_shared_ptr<Y>::value>* = nullptr>
        V to() const {            
            return reinterpret_cast<V>(_value);
        }

        template<typename V>
        operator V() const {
            return to<V>();
        }

        type_reference get() { return _value; }
        
        template <typename Y = T, typename std::enable_if_t<is_unique_ptr<Y>::value || is_shared_ptr<Y>::value>* = nullptr>  
        operator type_reference() const { 
            return *_value.get(); 
        }  

        template <typename Y = T, typename std::enable_if_t<is_unique_ptr<Y>::value || is_shared_ptr<Y>::value>* = nullptr>  
        operator typename unique_ptr_type<Y>::underlying_type&() { 
            return *_value.get(); 
        }  

        template <typename Y = T, typename std::enable_if_t<!is_unique_ptr<Y>::value && !is_shared_ptr<Y>::value>* = nullptr>      
        operator type() { return get(); }   

        template<typename N>
        auto operator[](const N index) { return _value[index]; }

        template<typename X>
        X as() {
            return (X)result;
        }

    private:
        type_reference _value;
    };

    template <typename T>
    struct readonly_t<T, std::true_type> { 
    public:
        
        using type = typename std::remove_reference<T>::type;
        using type_pointer = typename std::remove_reference<T>::type*;
        using type_reference = typename std::remove_reference<T>::type&;

        readonly_t(T value) : 
            _value(std::addressof(value)) {}
        

        readonly_t(const readonly_t&) = delete;
        readonly_t& operator =(const readonly_t&) = delete;
        ~readonly_t() = default;

        type_reference get() { return _value; }
        operator T() { return get(); }

        template<typename X>
        X as() {
            return (X)result();
        }

    private:
        type_pointer _value;
    };


} // namespace wry
