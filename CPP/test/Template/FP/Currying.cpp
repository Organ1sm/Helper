#include <iostream>
#include <string>
#include "Template/FP/Currying.hpp"

class CallableTest
{
  public:

    template <typename T1, typename T2, typename T3>
    auto operator()(T1 x, T2 y, T3 z) const
    {
        return x + y + z;
    }

    template <typename T1, typename T2>
    auto operator()(T1 x, T2 y) const
    {
        return x + y;
    }
};

std::string concat(std::string a, std::string b) { return (a += " ") += b; }


int main()
{
    auto add = [](int a, double b, int c, float d) { return a + b + c + d; };

    auto addCurried = makeCurried(add);
    std::cout << addCurried(1)(2.0)(64)(0.5f) << '\n';
    std::cout << addCurried(1, 2.0)(64, 0.5f) << '\n';
    std::cout << addCurried(1, 2.0, 64, 0.5f) << "\n\n";


    auto lessCurried = makeCurried(std::less<>());
    std::cout << lessCurried(42, 1) << '\n';

    auto greaterThan42 = lessCurried(42);
    std::cout << greaterThan42(1.0) << '\n';
    std::cout << greaterThan42(100.0) << "\n\n";


    CallableTest ct;
    auto ctCurried = makeCurried(ct);
    std::cout << ctCurried(1)(2, 3) << '\n';

    auto ctCurriedOne = Curried(ct, 1);
    std::cout << ctCurriedOne(2, 3) << "\n\n";

    using namespace std::string_literals;
    auto ctConcatCurried = makeCurried(concat);
    std::cout << ctConcatCurried("miao"s)("gua"s) << "\n\n";

    auto func = [](int &a, int &b) {
        a++;
        b--;
    };

    int a = 1;
    int b = 2;

    auto funcCurried = makeCurried(func);
    funcCurried(std::ref(a), std::ref(b));

    std::cout << a << " " << b << "\n";
}
