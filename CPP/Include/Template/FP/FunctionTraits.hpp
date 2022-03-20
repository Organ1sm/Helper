#pragma once

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <type_traits>
#include <utility>
namespace FunctionUtils
{
    template <typename Function>
    struct FunctionTraits;

    // normal function, static member function.
    template <typename Return, typename... Args>
    struct FunctionTraits<Return(Args...)>
    {
        using FunctionType = std::function<Return(Args...)>;
        using ReturnType   = Return;

        static constexpr std::size_t arity = sizeof...(Args);

        template <std::size_t I>
        struct argument
        {
            static_assert(I < arity, "Error: invaild index of this function's parameter.");
            using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
        };
    };

    // function pointer, &f
    template <typename Return, typename... Args>
    struct FunctionTraits<Return (*)(Args...)> : public FunctionTraits<Return(Args)...>
    {};

    // std::function
    template <typename Return, typename... Args>
    struct FunctionTraits<std::function<Return(Args...)>> : public FunctionTraits<Return(Args...)>,
                                                            FunctionTraits<Return (*)(Args...)>
    {};

    // functor, callable object struct with overload operator()
    template <typename Functor>
    struct FunctionTraits : public FunctionTraits<decltype(&Functor::operator())>
    {};

    // lambda expression, const member function pointer
    template <typename Class, typename Return, typename... Args>
    struct FunctionTraits<Return (Class::*)(Args...) const> : public FunctionTraits<Return(Args...)>
    {};

    // member object pointer
    template <typename Class, typename Return>
    struct FunctionTraits<Return(Class::*)> : public FunctionTraits<Return()>
    {};

    // clear reference F&, F&&
    template <typename F>
    struct FunctionTraits<F &> : public FunctionTraits<F>
    {};

    template <typename F>
    struct FunctionTraits<F &&> : public FunctionTraits<F>
    {};

    // make_func(), return a std::function<> object from function-like object
    template <typename Function>
    auto makeFunction(Function &&f)
    {
        typename FunctionTraits<Function>::FunctionType f_ = std::forward<decltype(f)>(f);
        return std::forward<decltype(f_)>(f_);
    }

    // arity(), return numbers of parameters
    template <typename Func>
    inline constexpr std::size_t arity(Func &&)
    {
        return FunctionTraits<std::remove_reference_t<Func>>::arity;
    }

    // argument_type<Func, I>::type, return I-th parameter's type, I start from 0
    template <typename Func, std::size_t I>
    struct ArgumentType
    {
        using type = typename FunctionTraits<Func>::template argument<I>::type;
    };



}    // namespace FunctionUtils