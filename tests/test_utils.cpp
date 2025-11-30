#include <catch2/catch_test_macros.hpp>
#include "utils.hpp"
#include <fstream>

TEST_CASE("Read lines from file", "[utils]") {
    // Create a test file
    const std::string testFile = "test_input.txt";
    {
        std::ofstream out(testFile);
        out << "line 1\n";
        out << "line 2\n";
        out << "line 3\n";
    }

    auto lines = utils::readLines(testFile);

    REQUIRE(lines.size() == 3);
    REQUIRE(lines[0] == "line 1");
    REQUIRE(lines[1] == "line 2");
    REQUIRE(lines[2] == "line 3");

    // Clean up
    std::remove(testFile.c_str());
}

TEST_CASE("Read entire file", "[utils]") {
    const std::string testFile = "test_input.txt";
    {
        std::ofstream out(testFile);
        out << "Hello\nWorld";
    }

    std::string content = utils::readFile(testFile);

    REQUIRE(content == "Hello\nWorld");

    std::remove(testFile.c_str());
}

TEST_CASE("Split string by delimiter", "[utils]") {
    std::string input = "1,2,3,4,5";
    auto parts = utils::split(input, ',');

    REQUIRE(parts.size() == 5);
    REQUIRE(parts[0] == "1");
    REQUIRE(parts[4] == "5");
}

TEST_CASE("Split string by space", "[utils]") {
    std::string input = "hello world from advent";
    auto parts = utils::split(input, ' ');

    REQUIRE(parts.size() == 4);
    REQUIRE(parts[0] == "hello");
    REQUIRE(parts[3] == "advent");
}

TEST_CASE("Trim whitespace", "[utils]") {
    REQUIRE(utils::trim("  hello  ") == "hello");
    REQUIRE(utils::trim("\t\ntest\r\n") == "test");
    REQUIRE(utils::trim("no spaces") == "no spaces");
    REQUIRE(utils::trim("   ").empty());
}

TEST_CASE("File not found throws exception", "[utils]") {
    REQUIRE_THROWS_AS(utils::readLines("nonexistent.txt"), std::runtime_error);
}