#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

namespace utils {
    // Read file and return lines as vector of strings
    std::vector<std::string> readLines(const std::string& filepath);

    // Read entire file as a single string
    std::string readFile(const std::string& filepath);

    // Split a string by delimiter
    std::vector<std::string> split(const std::string& str, char delimiter);

    // Trim whitespace from both ends
    std::string trim(const std::string& str);
}

#endif