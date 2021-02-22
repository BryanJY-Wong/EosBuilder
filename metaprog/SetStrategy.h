#pragma once

template<typename TOptions, typename T, T TOptions::* Member>
struct SetStrategy
{
    static void Set(TOptions& dst, T const& src)
    {
        dst.*Member = src;
    }
};

// Example

enum Flag { f1 = 1, f2 = 2, f3 = 4 };

template<typename TOptions, Flag TOptions::*Member>
struct SetStrategy<TOptions, Flag, Member>
{
    static void Set(TOptions& dst, Flag const& src)
    {
        dst.*Member |= src;
    }
};
