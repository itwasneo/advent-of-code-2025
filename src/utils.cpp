#include "utils.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace utils {

    std::vector<std::string> readLines(const std::string& filepath) {
        std::ifstream file(filepath);

        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filepath);
        }

        std::vector<std::string> lines;
        std::string line;

        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        file.close();
        return lines;
    }

    std::string readFile(const std::string& filepath) {
        std::ifstream file(filepath);

        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filepath);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        return buffer.str();
    }

    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;

        while (std::getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }

        return tokens;
    }

    std::string trim(const std::string& str) {
        const auto start = str.find_first_not_of(" \t\n\r");
        if (start == std::string::npos) {
            return "";
        }

        const auto end = str.find_last_not_of(" \t\n\r");
        return str.substr(start, end - start + 1);
    }
}