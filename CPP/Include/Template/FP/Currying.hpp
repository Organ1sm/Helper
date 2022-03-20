#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <type_traits>

template <typename Function, typename... CaputuredArgs>
class Curried
{
    using CaputuredArgsTuple = std::tuple<std::decay_t<CaputuredArgs>...>;

    Function Func;
    CaputuredArgsTuple Caputured;

    template <typename... Args>
    static constexpr decltype(auto) caputureByCopy(Args &&...args)
    {
        return std::tuple<std::decay_t<Args>...>(std::forward<Args>(args)...);
    }

  public:

    constexpr Curried(Function func, CaputuredArgs &&...args)
        : Func {func}, Caputured {caputureByCopy(std::move(args)...)}

    {}

    constexpr Curried(Function func, std::tuple<CaputuredArgs...> &&args)
        : Func {func}, Caputured {std::forward<std::tuple<CaputuredArgs...>>(args)}
    {}

    template <typename... NewArgs>
    constexpr decltype(auto) operator()(NewArgs &&...args)
    {
        auto newArgs = caputureByCopy(std::forward<NewArgs>(args)...);
        auto allArgs = std::tuple_cat(Caputured, std::move(newArgs));

        if constexpr (std::is_invocable_v<Function, CaputuredArgs..., NewArgs...>)
            return std::apply(Func, std::move(allArgs));
        else
            return Curried<Function, CaputuredArgs..., std::decay_t<NewArgs>...>(Func,
                                                                                 std::move(allArgs));
    }
};

template <typename Function>
constexpr auto makeCurried(Function &&func)
{
    return Curried<Function>(std::forward<Function>(func));
}


