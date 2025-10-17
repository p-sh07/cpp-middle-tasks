#include <print>
#include "parallel_min.h"

int main() {
    {
        //1.Parallel min:
        auto data = parallel_min::GenerateRandomVec();
        auto result = parallel_min::parallel_min(data);
        std::println("1.Parallel Min: Vec size[{}], min = {}", data.size(), result);
    }
    return 0;
}