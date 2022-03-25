#include "Template/FP/FunctionTraits.hpp"

#include <functional>
#include <ios>
#include <iostream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <cxxabi.h>

std::string realName(const std::type_info &info)
{
    int status = 0;
    return std::string(abi::__cxa_demangle(info.name(), 0, 0, &status));
}

auto profile = [](auto f) {
    using traits = FunctionUtils::FunctionTraits<decltype(f)>;
    std::cout << "\tarity=" << FunctionUtils::arity(f) << std::endl;

    const auto &ret  = typeid(typename traits::ReturnType);
    const auto &func = typeid(typename traits::FunctionType);
    std::cout << "ReturnType = " << realName(ret);
    std::cout << ", FuncType = " << realName(func) << std::endl;
    std::cout << "**************************" << std::endl;
};

double fun(int, int) { return 0; }

struct Foo
{
    double f = 5.0;
    int operator()(int a, int b) const { return a - b; }
    bool odd(int a) { return a % 2; }
} sub;

auto bar                         = [](int a, double b, int c) -> double { return a + b + c; };
std::function<int(int, int)> add = [](int a, int b) -> int { return a + b; };

#define DISPLAY_PROFILE(f)    \
    do {                      \
        std::cout << "  " #f; \
        profile(f);           \
    }                         \
    while (0);

int main()
{
    std::cout << "=================== Struct Function Traits ===================" << std::endl;

    using traits = FunctionUtils::FunctionTraits<decltype(bar)>;
    std::cout << " bar: \t arity=" << traits::arity << std::endl;
    std::cout << std::boolalpha;
    std::cout << "double ? " << std::is_same<double, traits::ReturnType>::value << '\t';
    std::cout << "int ? " << std::is_same<int, traits::argument<0>::type>::value << '\t';
    std::cout << "int ? " << std::is_same<int, traits::argument<1>::type>::value << '\t';
    std::cout << "int ? " << std::is_same<int, traits::argument<2>::type>::value << std::endl;


    std::cout << "=================== Arity(), makeFunc() ========================" << std::endl;
    std::cout << "Normal Function:\n";
    auto f1 = FunctionUtils::makeFunction(fun);
    DISPLAY_PROFILE(fun);
    DISPLAY_PROFILE(f1);

    std::cout << "std::function object:\n";
    auto add_ = FunctionUtils::makeFunction(add);
    DISPLAY_PROFILE(add);
    DISPLAY_PROFILE(add_);

    std::cout << "Lambda Object:\n";
    auto bar_ = FunctionUtils::makeFunction(bar);
    DISPLAY_PROFILE(bar);
    DISPLAY_PROFILE(bar_);

    std::cout << "Functor Object:\n";
    auto sub_ = FunctionUtils::makeFunction(sub);
    DISPLAY_PROFILE(sub);
    DISPLAY_PROFILE(sub_);


    std::cout << "===================== Member Object, Member Function ============\n";
    std::cout << "Member object pointer : \n";
    DISPLAY_PROFILE(&Foo::f);
    // std::cout << "Member Function instance:\n";
    // DISPLAY_PROFILE(sub.odd);
    std::cout << "Member Function pointer : \n";
    DISPLAY_PROFILE(&Foo::odd);

    std::cout << "====================== Makefunction with lambda expression =========\n";
    auto mul = FunctionUtils::makeFunction([](int a, int b) -> int { return a * b; });
    DISPLAY_PROFILE(mul);


    std::cout << "====================== Struct Argument Type =================" << std::endl;
    const auto &ret = typeid(typename traits::ReturnType);
    const auto &fun = typeid(typename traits::FunctionType);
    const auto &fst = typeid(typename FunctionUtils::ArgumentType<decltype(bar), 0>::type);
    const auto &snd = typeid(typename FunctionUtils::ArgumentType<decltype(bar), 1>::type);
    const auto &trd = typeid(typename FunctionUtils::ArgumentType<decltype(bar), 2>::type);

    std::cout << " bar: arity = " << FunctionUtils::arity(bar) << std::endl;

    std::cout << "ReturnType = " << realName(ret) << ", ";
    std::cout << "FuncType = " << realName(fun) << std::endl;
    std::cout << "FuncType = std::function<" << realName(ret) << " (";
    std::cout << realName(fst) << ", ";
    std::cout << realName(snd) << ", ";
    std::cout << realName(trd) << ")>" << std::endl;

    return 0;
}