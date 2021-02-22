#pragma once
#include "ApiVersion.h"
#include "Caller.h"
#include "Lists.h"
#include "PodBuilder.h"

template<typename TBuilder, typename LOptionals, typename LNonOptionals = NonOptionalList<typename LOptionals::type>>
struct BuilderBase;

template<typename TBuilder, typename TOptions, auto... FOptionals, auto... FNonOptionals>
struct BuilderBase<TBuilder, OptionalList<TOptions, FOptionals...>, NonOptionalList<TOptions, FNonOptionals...>> :
    PodBuilder<FieldList<TOptions, FOptionals..., FNonOptionals...>, NonOptionalList<TOptions, FNonOptionals...>>
{
    static_assert(!HasApiVersion<TOptions>::value || IsDefined<ApiVersion<TOptions>>::value, "You forgot the ApiVersion!");
private:
    using base_t = PodBuilder<FieldList<TOptions, FOptionals..., FNonOptionals...>, NonOptionalList<TOptions, FNonOptionals...>>;
    template<auto... M>
    static constexpr auto SetterFunction = &base_t::template SetField<M...>;
protected:
    BuilderBase() : base_t()
    {
        if constexpr (HasApiVersion<TOptions>::value)
        {
            this->Options.ApiVersion = ApiVersion<TOptions>::value;
        }
    }
    template<typename LArgs, auto... M>
    using CustomSetValue = Caller<TBuilder, SetterFunction<M...>, LArgs>;
    template<auto... M>
    using SetValue = CustomSetValue<TypeList<Member_t<M>...>, M...>;
    template<auto M>
    using SetBool = CustomSetValue<TypeList<bool const&>, M>;

    template<size_t N>
    static constexpr auto OptionalField = Indexer<N, FOptionals...>::value;
    template<size_t N>
    static constexpr auto NonOptionalField = Indexer<N, FNonOptionals...>::value;
    template<size_t N>
    static constexpr auto Field = Indexer<N, FOptionals..., FNonOptionals...>::value;
};
