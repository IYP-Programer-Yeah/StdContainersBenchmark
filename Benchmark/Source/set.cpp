#include <benchmark/benchmark.h>

#include <set>
#include <cstdlib>

std::set<int> ConstructRandomSet(const std::size_t size)
{
    std::set<int> benchmark_case;
    for (int i = 0; i < size; ++i)
        benchmark_case.emplace(static_cast<int>(std::rand() % size));

    return benchmark_case;
}

void SetSearchBigON(benchmark::State &state)
{
    auto benchmark_case = ConstructRandomSet(state.range(0));
    for (auto _ : state)
    {
        state.PauseTiming();
        const auto test_item = static_cast<int>(std::rand() % (state.range(0) * 2));
        state.ResumeTiming();
        benchmark::DoNotOptimize(benchmark_case.find(test_item));
    }
    state.SetComplexityN(state.range(0));
}

void SetInsertionBigON(benchmark::State &state)
{
    auto benchmark_case = ConstructRandomSet(state.range(0));
    for (auto _ : state)
    {
        state.PauseTiming();
        const auto test_item = static_cast<int>(std::rand() % (state.range(0) * 2));
        state.ResumeTiming();
        const auto emplace_result = benchmark_case.emplace(test_item);
        benchmark::DoNotOptimize(benchmark_case);
        state.PauseTiming();
        if (emplace_result.second)
            benchmark_case.erase(emplace_result.first);
        state.ResumeTiming();
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(SetSearchBigON)
    ->RangeMultiplier(2)
    ->Range(1 << 10, 1 << 16)
    ->Complexity();

BENCHMARK(SetInsertionBigON)
    ->RangeMultiplier(2)
    ->Range(1 << 10, 1 << 16)
    ->Complexity();
