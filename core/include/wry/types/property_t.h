#pragma once

#include <type_traits>
#include "wry/types/traits.h"

namespace wry {
    template <typename T, typename = typename std::is_reference<T>::type>
    struct property_t { };

    template <typename T>
    struct property_t<T, std::false_type> { 
    public:
    
        using type = T;
        using type_pointer = typename std::remove_reference<T>::type*;
        using type_reference = typename std::remove_reference<T>::type&;

        property_t(type_reference value) : 
            _value(value) {}

        //retval(const retval&) = delete;
        property_t& operator =(const property_t&) = delete;

        property_t& operator =(type_reference value) {
            set(value);
            return *this;
        }
        
        property_t& operator =(const type value) {
            set(value);
            return *this;
        }

        ~property_t() = default;

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

        property_t& set(type_reference value) { _value = value; return *this; }
        property_t& set(const type value) { _value = value; return *this; }
        
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

        template <typename Y = T, typename std::enable_if_t<std::is_pointer<Y>::value || is_unique_ptr<Y>::value || is_shared_ptr<Y>::value>* = nullptr>
        type_reference operator->() { return _value; }

        template <typename Y = T, typename std::enable_if_t<!std::is_pointer<Y>::value && !is_unique_ptr<Y>::value && !is_shared_ptr<Y>::value>* = nullptr>
        type_pointer operator->() { return &_value; }

        template<typename N>
        auto operator[](const N index) { return _value[index]; }

        template<typename X>
        X as() {
            return (X)get();
        }

    private:
        type_reference _value;
    };

    template <typename T>
    struct property_t<T, std::true_type> { 
    public:
        
        using type = typename std::remove_reference<T>::type;
        using type_pointer = typename std::remove_reference<T>::type*;
        using type_reference = typename std::remove_reference<T>::type&;

        property_t(T value) : 
            _value(std::addressof(value)) {}
        

        property_t(const property_t&) = delete;
        property_t& operator =(const property_t&) = delete;
        ~property_t() = default;

        type_reference get() { return _value; }
        property_t set(type_reference value) { _value = value; return this; }

        operator T() { return get(); }

        type_pointer operator->() { return _value; }

        template<typename X>
        X as() {
            return (X)get();
        }

    private:
        type_pointer _value;
    };


} // namespace wry
