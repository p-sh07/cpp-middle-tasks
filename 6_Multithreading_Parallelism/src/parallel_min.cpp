//
// Created by Pavel on 17.10.2025.
//
#include "parallel_min.h"

namespace parallel_min {
std::vector<int> GenerateRandomVec(size_t size) {
    std::mt19937 gen{std::random_device()()};
    std::uniform_int_distribution distr(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    std::vector<int> result;
    result.reserve(size);
    rg::generate_n(std::back_inserter(result), size, [&](){ return distr(gen); });

    return result;
}
}