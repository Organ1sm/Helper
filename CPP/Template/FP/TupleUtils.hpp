#include <iostream>
#include <string>
#include <tuple>
#include <utility>

namespace tupleUtil
{
    template <typename Function, typename Tuple, std::size_t N>
    struct TupleHelper
    {
        static void handler(Function func, const Tuple &t)
        {
            TupleHelper<Function, Tuple, N - 1>::handler(func, t);
            func(std::get<N - 1>(t), N - 1);
        }
    };


    template <typename Function, typename Tuple>
    struct TupleHelper<Function, Tuple, 1>
    {
        static void handler(Function func, const Tuple &t) { func(std::get<0>(t), 0); }
    };

    template <typename Function, typename... Args>
    void manipulateTuple(Function f, const std::tuple<Args...> &t)
    {
        TupleHelper<Function, decltype(t), sizeof...(Args)>::handler(f, t);
    }

    template <typename... Args>
    void printTuple(const std::tuple<Args...> &t)
    {
        std::cout << "(";

        auto worker = [](auto _, std::size_t index) {
            if (index != 0) std::cout << ", ";
            std::cout << _;
        };
        manipulateTuple(worker, t);

        std::cout << ")";
        std::cout << std::endl;
    }

    template <typename T, typename... Ts>
    auto head(std::tuple<T, Ts...> t)
    {
        return std::get<0>(t);
    }

    template <std::size_t... Ns, typename... Ts>
    auto tailImpl(std::index_sequence<Ns...>, std::tuple<Ts...> t)
    {
        return std::make_tuple(std::get<Ns + 1u>(t)...);
    }

    template <typename... Ts>
    auto tail(std::tuple<Ts...> t)
    {
        return tailImpl(std::make_index_sequence<sizeof...(Ts) - 1u>(), t);
    }

    template <std::size_t... Ns, typename... Ts>
    auto initImpl(std::index_sequence<Ns...>, std::tuple<Ts...> t)
    {
        return std::make_tuple(std::get<Ns>(t)...);
    }

    template <typename... Ts>
    auto init(std::tuple<Ts...> t)
    {
        return initImpl(std::make_index_sequence<sizeof...(Ts) - 1u>(), t);
    }

    template <typename... Ts>
    auto last(std::tuple<Ts...> t)
    {
        std::cout << sizeof...(Ts) << std::endl;
        return std::get<sizeof...(Ts) - 1u>(t);
    }
    template <typename T>
    constexpr auto size(const T &t)
    {
        return std::tuple_size<T>::value;
    }template <typename T>
    constexpr auto size(const T &t)
    {
        return std::tuple_size<T>::value;
    }
    template <typename T>
    auto last2(T t)
    {
        return std::get<std::tuple_size<T>::value - 1u>(t);
    }


}    // namespace tupleUtil
