#pragma once
#include "FieldParser.h"
#include <type_traits>

template<typename TStruct, auto... Fields>
struct AssertFields
{
    static_assert((std::is_same<TStruct, Class_t<Fields>>::value && ...));
    using type = TStruct;
};

template<typename TStruct>
struct AssertFields<TStruct> { using type = TStruct; };

template<typename TStruct, auto... Fields>
struct FieldList : AssertFields<TStruct, Fields...> {};

template<typename TStruct, auto... Fields>
struct NonOptionalList : AssertFields<TStruct, Fields...> {};

template<typename TStruct, auto... Fields>
struct OptionalList : AssertFields<TStruct, Fields...> {};

template<typename... T>
struct TypeList {};

template<auto Target, auto... List>
struct Contains;

template<auto Target>
struct Contains<Target> : std::false_type {};

template<auto Target, auto Head, auto... Tail>
struct Contains<Target, Head, Tail...> : Contains<Target, Tail...> {};

template<auto Target, auto... Tail>
struct Contains<Target, Target, Tail...> : std::true_type {};

template <auto Target, auto... List>
struct GetIdx;

template <auto Target, auto... Tail>
struct GetIdx<Target, Target, Tail...>
{
    static constexpr size_t value = 0;
};

template <auto Target, auto Head, auto... Tail>
struct GetIdx<Target, Head, Tail...>
{
    static constexpr size_t value = 1 + GetIdx<Target, Tail...>::value;
};

template <auto Target>
struct GetIdx<Target>
{
    static_assert(!sizeof(decltype(Target)), "Target not in list");
};

template<size_t N, auto... List>
struct Indexer;

template<auto Head, auto... Tail>
struct Indexer<0, Head, Tail...>
{
    static constexpr auto value = Head;
};

template<size_t N, auto Head, auto... Tail>
struct Indexer<N, Head, Tail...> : Indexer<N - 1, Tail...> {};

template<size_t N>
struct Indexer<N> { static_assert(!N && N, "Index out of range"); };
