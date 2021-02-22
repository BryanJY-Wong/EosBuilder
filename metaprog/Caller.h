#pragma once
#include "Lists.h"

template<typename TObject, auto Function, typename TList>
struct Caller;
template<typename TObject, auto Function, typename... Args>
struct Caller<TObject, Function, TypeList<Args...>>
{
private:
    friend TObject;
    TObject* Instance;
    Caller(TObject* instance) : Instance(instance) {}
public:
    Caller() = delete;
    Caller(Caller const& other) = delete;
    Caller(Caller&& other) = delete;
    Caller& operator=(Caller const& other) = delete;
    Caller& operator=(Caller&& other) = delete;
    ~Caller() = default;

    TObject& operator()(Args const&... args)
    {
        (Instance->*Function)(args...);
        return *Instance;
    }
};
