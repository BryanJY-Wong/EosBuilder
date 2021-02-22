#pragma once
#include "Lists.h"
#include "FieldParser.h"
#include "SetStrategy.h"
#include "Validator.h"
#include <tuple>

template<typename TFieldList, typename TNonOptionalList>
struct PodBuilder;

template<typename TOptions, auto... AllFields, auto... Validatable>
struct PodBuilder<FieldList<TOptions, AllFields...>, NonOptionalList<TOptions, Validatable...>>
{
    template<auto Member>
    using Validator_t = Validator<Class_t<Member>, Member_t<Member>, Member>;
    template<auto Member>
    using Strategy = SetStrategy<TOptions, Member_t<Member>, Member>;

    std::tuple<Validator_t<Validatable>...> Validators;
    TOptions Options;
    PodBuilder() : Validators(), Options() {}

    bool ValidateFields()
    {
        if constexpr (sizeof...(Validatable) > 0)
        {
            return (std::get<Validator_t<Validatable>>(Validators).Check(Options) && ...);
        }

        return true;
    }

    template<auto M>
    void SetValidator()
    {
        if constexpr (HasSetFunction<Validator_t<M>>::value)
        {
            std::get<Validator_t<M>>(Validators).Set(Options);
        }
    }

    template<auto M>
    void OnSetField(Member_t<M> const& value)
    {
        Strategy<M>::Set(Options, value);
        if constexpr (Contains<M, Validatable...>::value)
        {
            SetValidator<M>();
        }
    }

    template<auto... M>
    void SetField(Member_t<M> const&... value)
    {
        (OnSetField<M>(value), ...);
    }

    TOptions* Build()
    {
        // assert ValidateFields();
        return &Options;
    }
};
