#pragma once

template<typename T>
struct FieldParser
{
    static_assert(!sizeof(T), "Invalid type, must be a field pointer");
};

template<typename T, typename TOptions>
struct FieldParser<T TOptions::*>
{
    using class_t = TOptions;
    using member_t = T;
};

template<auto Field>
using Member_t = typename FieldParser<decltype(Field)>::member_t;
template<auto Field>
using Class_t = typename FieldParser<decltype(Field)>::class_t;
