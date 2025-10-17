//
// Created by Pavel on 17.10.2025.
//

#pragma once

#include <algorithm>
#include <functional>
#include <span>
#include <thread>
#include <vector>
#include <ranges>
#include <random>
#include <print>

#define PRINT_THREAD_INFO

namespace parallel_min {
namespace rg = std::ranges;
namespace vw = std::views;

static constexpr size_t MT_THRESHOLD = 1024 * 16;

std::vector<int> GenerateRandomVec(size_t size = MT_THRESHOLD + 1);

// Функция, которая будет запускаться в отдельных потоках
template <typename T>
void find_chunk_min(std::span<const T> chunk, T &result_location) {
    result_location = std::ranges::min(chunk);

#ifdef PRINT_THREAD_INFO
    std::println("\t-Thread_id[{}]: min = {}", std::this_thread::get_id(), result_location);
#endif
}

template <typename T>
T parallel_min(const std::vector<T> &data) {
    if (data.empty()) {
        throw std::invalid_argument("Cannot find minimum of empty vector");
    }

    // Сколько в процессоре ядер. Вернёт 0, если нет поддержки потоков
    const size_t max_threads = std::thread::hardware_concurrency();

    // Многопоточность выгодна, только если элементов больше, чем MT_THRESHOLD
    // Здесь MT_THRESHOLD искусственно занижен, чтобы код использовал
    // многоточность без необходимости заводить много мегабайт данных
    if (data.size() <= MT_THRESHOLD || max_threads <= 1) {
        return rg::min(data);
    }

    // Гарантируем, что ни один поток не получит пустой блок данных
    const size_t num_threads = std::min(max_threads, data.size());

#ifdef PRINT_THREAD_INFO
    std::println("=================== PRINT THREAD INFO ===================");
    std::println("Number of threads = {}, starting:", num_threads);
#endif

    std::vector<T> partial_mins(num_threads);  // результаты работы потоков
    std::vector<std::jthread> threads;

    /**
     * Performs integer ceiling division to ensure all elements are evenly distributed
     * across threads, even when data.size() is not perfectly divisible by num_threads.
     * -> Adding (num_threads - 1) before division forces rounding up when there’s a remainder.
     * This ensures every element is covered and no data at the end is left unassigned to a thread.
     */
    size_t chunk_size = (data.size() + num_threads - 1) / num_threads;
    auto it = data.begin();

    for (auto i : vw::iota(0u, num_threads)) {
        auto start_it = it;
        auto end_it = data.end() - start_it > chunk_size ? start_it + chunk_size : data.end();

        threads.emplace_back(find_chunk_min<T>, std::span{start_it, end_it}, std::ref(partial_mins[i]));
        it = end_it;
    }

    // Завершить все потоки перед использованием результата
    rg::for_each(threads, [](auto& t) { t.join(); });

#ifdef PRINT_THREAD_INFO
    std::println("=========================================================");
#endif
    // Минимум среди частичных минимумов
    return rg::min(partial_mins);
}
}