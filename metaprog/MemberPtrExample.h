#pragma once
#include <type_traits>

struct MemberPtrExample
{
    int Integer;
    int Integer2;
    void Function(int) {}
};

// syntax examples
static_assert(std::is_same<decltype(MemberPtrExample::Integer), int>::value);
static_assert(std::is_same<decltype(&MemberPtrExample::Integer), int MemberPtrExample::*>::value);
static_assert(std::is_same<decltype(&MemberPtrExample::Integer), decltype(&MemberPtrExample::Integer2)>::value);
static_assert(&MemberPtrExample::Integer2 != &MemberPtrExample::Integer);

inline void member_ptr()
{
    auto ptr = &MemberPtrExample::Integer;
    auto fPtr = &MemberPtrExample::Function;
    MemberPtrExample m{};
    m.*ptr = 8;
    (m.*fPtr)(m.*ptr);
}
