#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include "../include/day_01.hpp"

TEST_CASE("day_01 part1 solution is correct", "[DAY_01]") {
    REQUIRE(solve_01_01("./input/input_01") == 1007);
}

TEST_CASE("data_01_01 part1 example solution is correct", "[DAY_01]") {
    REQUIRE(solve_01_01("./input/example_01") == 3);
}

TEST_CASE("day_01 part2 solution is correct", "[DAY_01]") {
    REQUIRE(solve_01_02("./input/input_01") == 5820);
}

TEST_CASE("data_01_02 part2 example solution is correct", "[DAY_01]") {
    REQUIRE(solve_01_02("./input/example_01") == 6);
}

TEST_CASE("day_01 part1 solution benchmark", "[DAY_01]") {
    BENCHMARK("day_01 part1 solution benchmark") {
        volatile auto result = solve_01_01("./input/input_01");
        (void)result;
    };
}

TEST_CASE("day_02 part2 solution benchmark", "[DAY_01]") {
    BENCHMARK("day_01 part2 solution benchmark") {
        volatile auto result = solve_01_02("./input/input_01");
        (void)result;
    };
}
