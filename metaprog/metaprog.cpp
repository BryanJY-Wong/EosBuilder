#include <iostream>
#include "BuilderBase.h"
#include "Lists.h"
#include "MemberPtrExample.h"

#define EOS_EXAMPLE_API_LATEST 23

typedef int EOS_Bool;

struct EOS_ExampleOptions
{
    int ApiVersion;
    int Integer;
    float Float;
    char const* String;
    EOS_Bool bIsSpecial;
    int* Array;
    int ArraySize;
};

template<>
struct ApiVersion<EOS_ExampleOptions> : Version<EOS_EXAMPLE_API_LATEST> {};

static_assert(ApiVersion<EOS_ExampleOptions>::value == EOS_EXAMPLE_API_LATEST);

namespace EOS
{
    struct ExampleOptionsBuilder :
        BuilderBase<ExampleOptionsBuilder,
        OptionalList<EOS_ExampleOptions,
            &EOS_ExampleOptions::Float,
            &EOS_ExampleOptions::Array,
            &EOS_ExampleOptions::ArraySize>,
        NonOptionalList<EOS_ExampleOptions,
            &EOS_ExampleOptions::Integer,
            &EOS_ExampleOptions::bIsSpecial,
            &EOS_ExampleOptions::String>>
    {
        SetValue<OptionalField<0>> Float{ this };

        SetValue<OptionalField<1>, OptionalField<2>> Array{ this };

        SetValue<NonOptionalField<0>> Integer{ this };

        SetBool<NonOptionalField<1>> IsSpecial{ this };

        SetValue<NonOptionalField<2>> String{ this };
    };
}

template<typename T, size_t N>
constexpr size_t SizeOf(T(&array)[N]) { return N; }

int main()
{
    using namespace std;
    using namespace EOS;
    cout << boolalpha;
    int array[] = { 1, 2, 3 };
    ExampleOptionsBuilder b;
    // b.SetField<&EOS_ExampleOptions::Integer>(4); // this is ugly

    cout << b.Build()->ApiVersion << endl; // 23
    cout << b.ValidateFields() << endl; // false
    cout << b.Integer(724234)
        .String("Hello!")
        .IsSpecial(false)
        .Build()->Integer << endl; // 724234
    cout << b.Build()->String << endl; // Hello!
    cout << b.ValidateFields() << endl; // true
    cout << b.Float(23.527215).Build()->Float << endl; // 23.527....
    b.Array(array, SizeOf(array));

    return 0;
}