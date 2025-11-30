#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include "../include/day_01.hpp"

TEST_CASE("day_01", "[check_answer]") {
    REQUIRE(solve_01() == 0);
}
