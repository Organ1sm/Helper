#pragma once

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>
namespace FunctionUtils
{
    template <typename Function>
    struct FunctionTraits;

    template <typename Return, typename... Args>
    struct FunctionTraits<Return(Args...)>
    {
        using FunctionType = std::function<Return(Args...)>;
        using ReturnType   = Return;

        static constexpr std::size_t arity = sizeof...(Args);

        template <std::size_t I>
        struct argument
        {
            static_assert(I < arity,
                          "Error: invaild index of this function's parameter.");
            using type =
                typename std::tuple_element<I, std::tuple<Args...>>::type;
        };
    };

    template <typename Return, typename... Args>
    struct FunctionTraits<Return (*)(Args...)>
        : public FunctionTraits<Return(Args)...>
    {};

    template <typename Return, typename... Args>
    struct FunctionTraits<std::function<Return(Args...)>>
        : public FunctionTraits<Return(Args...)>,
          FunctionTraits<Return (*)(Args...)>
    {};




}    // namespace FunctionUtils