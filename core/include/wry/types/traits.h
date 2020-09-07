#pragma once

#include <type_traits>
#include <memory>
#include <vector>

#include "wry/types/primitives.h"

template <class T>
struct is_unique_ptr : std::false_type
{};

template <class T, class D>
struct is_unique_ptr<std::unique_ptr<T, D>> : std::true_type
{};

template <class T>
struct unique_ptr_type
{};

template <class T, class D>
struct unique_ptr_type<std::unique_ptr<T, D>>
{    
    using type = std::unique_ptr<T, D>;
    using underlying_type = T;
    using delete_type = D;
};

template <class T>
struct is_shared_ptr : std::false_type
{};

template <class T>
struct is_shared_ptr<std::shared_ptr<T>> : std::true_type
{};

template <typename T>
struct is_indexable  : std::false_type
{ };

template <typename T, typename A>
struct is_indexable<std::vector<T, A>> : std::true_type
{ };

template <typename T, std::size_t N>
struct is_indexable<std::array<T, N>> : std::true_type
{ };

