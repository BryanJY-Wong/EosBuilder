#pragma once
#include <type_traits>

template<typename TOptions>
struct FlagValidator
{
    bool m_Set = false;
    void Set(TOptions const&) { m_Set = true; }
    bool Check(TOptions const&) const { return m_Set; }
};

template<typename TOptions, typename FieldType, FieldType TOptions::* Field>
struct Validator : FlagValidator<TOptions>
{
    static_assert(std::is_integral_v<FieldType> || std::is_enum_v<FieldType>, "Sorry, I only work for integers or enums");
};

template<typename TOptions, typename FieldType, FieldType* TOptions::* Field>
struct Validator<TOptions, FieldType*, Field>
{
    static bool Check(TOptions const& value) { return value.*Field != nullptr; }
};

template<typename T, typename = void>
struct HasSetFunction : std::false_type {};

template<typename T>
struct HasSetFunction<T, std::void_t<decltype(&T::Set)>> : std::true_type {};
