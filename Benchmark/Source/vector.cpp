#include <benchmark/benchmark.h>

#include <vector>
#include <cstdlib>

std::vector<int> ConstructRandomVector(const std::size_t size)
{
    std::vector<int> benchmarkCase;
    benchmarkCase.reserve(static_cast<int>(size));
    for (int i = 0; i < size; ++i)
        benchmarkCase.emplace_back(static_cast<int>(std::rand() % size));

    return benchmarkCase;
}

void VectorSearchBigON(benchmark::State &state)
{
    auto benchmark_case = ConstructRandomVector(state.range(0));
    for (auto _ : state)
    {
        state.PauseTiming();
        const auto test_item = static_cast<int>(std::rand() % (state.range(0) * 2));
        state.ResumeTiming();
        benchmark::DoNotOptimize(std::find(benchmark_case.begin(), benchmark_case.end(), test_item));
    }
    state.SetComplexityN(state.range(0));
}

void VectorInsertionBigON(benchmark::State &state)
{
    const auto benchmark_case = ConstructRandomVector(state.range(0));
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

BENCHMARK(VectorSearchBigON)
    ->RangeMultiplier(2)
    ->Range(1 << 10, 1 << 16)
    ->Complexity();

BENCHMARK(VectorInsertionBigON)
    ->RangeMultiplier(2)
    ->Range(1 << 10, 1 << 16)
    ->Complexity();