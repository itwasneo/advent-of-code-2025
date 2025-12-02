#include "day_01.hpp"
#include "utils.hpp"

int solve_01_01(const std::string &input_file) {
    const auto lines = utils::readLines(input_file);
    int ptr = 50;
    int pwd = 0;
    for (auto move : lines) {
        char dir = move[0];
        int amt = std::stoi(move.substr(1));
        if (dir == 'L') {
            ptr -= amt;
        } else {
            ptr += amt;
        }

        ptr = ((ptr % 100) + 100) % 100;

        if (ptr == 0) {
            pwd += 1;
        }
    }
    return pwd;
}

auto crossed = [](int prev, int cur) { return (prev > 0 && cur < 0) || (prev < 100 && cur > 100); };

int solve_01_02(const std::string &input_file) {
    const auto lines = utils::readLines(input_file);
    int ptr = 50;
    int pwd = 0;
    for (auto move : lines) {
        int amt = std::stoi(move.substr(1));
        pwd += amt / 100;

        int mod_amt = amt % 100;
        int prev_ptr = ptr;

        ptr += (move[0] == 'L') ? -mod_amt : mod_amt;
        pwd += crossed(prev_ptr, ptr) ? 1 : 0;
        ptr = ((ptr % 100) + 100) % 100;
        pwd += (ptr == 0) ? 1 : 0;
    }
    return pwd;
}
