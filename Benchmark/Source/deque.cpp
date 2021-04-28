#include <benchmark/benchmark.h>

#include <deque>
#include <cstdlib>

std::deque<int> ConstructRandomDeque(const std::size_t size)
{
    std::deque<int> benchmark_case;
    for (int i = 0; i < size; ++i)
        benchmark_case.emplace_back(static_cast<int>(std::rand() % size));

    return benchmark_case;
}

void DequeSearchBigON(benchmark::State &state)
{
    auto benchmark_case = ConstructRandomDeque(state.range(0));
    for (auto _ : state)
    {
        state.PauseTiming();
        const auto test_item = static_cast<int>(std::rand() % (state.range(0) * 2));
        state.ResumeTiming();
        benchmark::DoNotOptimize(std::find(benchmark_case.begin(), benchmark_case.end(), test_item));
    }
    state.SetComplexityN(state.range(0));
}

void DequeInsertionBigON(benchmark::State &state)
{
    const auto benchmark_case = ConstructRandomDeque(state.range(0));
    auto new_benchmark_case = benchmark_case;
    for (auto _ : state)
    {
        state.PauseTiming();
        new_benchmark_case = benchmark_case;
        const auto test_item = static_cast<int>(std::rand() % (state.range(0) * 2));
        state.ResumeTiming();
        new_benchmark_case.emplace_back(test_item);
        benchmark::DoNotOptimize(new_benchmark_case);
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(DequeSearchBigON)
    ->RangeMultiplier(2)
    ->Range(1 << 10, 1 << 16)
    ->Complexity();

BENCHMARK(DequeInsertionBigON)
    ->RangeMultiplier(2)
    ->Range(1 << 10, 1 << 16)
    ->Complexity();
