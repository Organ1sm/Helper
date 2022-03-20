#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>
#include "Template/FP/TupleUtils.hpp"



int main()
{
    auto add  = [](int lhs, int rhs) { return lhs + rhs; };
    auto add3 = [](int x, int y, int z) { return x + y + z; };

    std::cout << std::apply(add, std::make_pair(1, 2)) << std::endl;
    std::cout << std::apply(add3, std::make_tuple(1, 2, 3)) << std::endl;

    std::cout << tupleUtil::TupleApply(add, std::make_pair(1, 2)) << std::endl;
    std::cout << tupleUtil::TupleApply(add3, std::make_tuple(1, 2, 3)) << std::endl;

    return 0;
}
