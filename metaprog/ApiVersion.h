#pragma once
#include <type_traits>

template<typename TOptions>
struct ApiVersion;

// SFINAE, Substitution Failure Is Not An Error
template<typename T, typename = void>
struct IsDefined : std::false_type {};
template<typename T>
struct IsDefined < T, std::enable_if_t<(sizeof(T) > 0)>> : std::true_type {};

static_assert(!IsDefined<ApiVersion<int>>::value);
static_assert(IsDefined<int>::value);
// Sfinae flow
// IsDefined<ApiVersion<int>> -> IsDefined<ApiVersion<int>, void> -> IsDefined<ApiVersion<int>, void> : false_type
// IsDefined<int> -> IsDefined<int, void> -> IsDefined<int, void> : true_type

template<typename T, typename = void>
struct HasApiVersion : std::false_type {};
template<typename T>
struct HasApiVersion<T, std::enable_if_t<std::is_same_v<decltype(T::ApiVersion), int>>> : std::true_type {};

static_assert(!HasApiVersion<int>::value);

template<int N>
using Version = std::integral_constant<int, N>;

// bool types
struct false_type { static constexpr bool value = false; };
struct true_type { static constexpr bool value = true; };

// enable if
template<bool,typename = void>
struct enable_if;
template<typename T>
struct enable_if<true, T> { using type = T; };
template<bool B, typename T>
using enable_if_t = typename enable_if<B, T>::type;
