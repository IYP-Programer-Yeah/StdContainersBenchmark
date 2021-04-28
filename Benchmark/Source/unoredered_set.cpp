#include <benchmark/benchmark.h>

#include <unordered_set>
#include <cstdlib>

std::unordered_set<int> ConstructRandomUnorderedSet(const std::size_t size)
{
    std::unordered_set<int> benchmark_case;
    for (int i = 0; i < size; ++i)
        benchmark_case.emplace(static_cast<int>(std::rand() % size));

    return benchmark_case;
}

void UnorderedSetSearchBigON(benchmark::State &state)
{
    auto benchmark_case = ConstructRandomUnorderedSet(state.range(0));
    for (auto _ : state)
    {
        state.PauseTiming();
        const auto test_item = static_cast<int>(std::rand() % (state.range(0) * 2));
        state.ResumeTiming();
        benchmark::DoNotOptimize(benchmark_case.find(test_item));
    }
    state.SetComplexityN(state.range(0));
}

void UnorderedSetInsertionBigON(benchmark::State &state)
{
    auto benchmark_case = ConstructRandomUnorderedSet(state.range(0));
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

BENCHMARK(UnorderedSetSearchBigON)
    ->RangeMultiplier(2)
    ->Range(1 << 10, 1 << 16)
    ->Complexity();

BENCHMARK(UnorderedSetInsertionBigON)
    ->RangeMultiplier(2)
    ->Range(1 << 10, 1 << 16)
    ->Complexity();
