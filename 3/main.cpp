#include <cmath>
#include <cstdint>
#include <fstream>
#include <print>
#include <string>
#include <vector>

std::vector<std::string> get_inputs(const std::string &file) {
    std::ifstream f{ file };
    std::vector<std::string> inputs{};
    for (std::string line; std::getline(f, line);) {
        inputs.push_back(line);
    }

    return inputs;
}

std::uint64_t get_joltage(const std::vector<std::string> &inputs) {
    std::uint64_t total{ 0 };
    for (const auto &bank : inputs) {
        int max{ bank.at(0) - '0' };
        int max_i{ 0 };
        for (std::string::size_type i = 1; i < bank.length() - 1; ++i) {
            if ((bank.at(i) - '0') > max) {
                max = bank.at(i) - '0';
                max_i = i;
            }
        }
        int max2{ bank.at(max_i + 1) - '0' };
        for (std::string::size_type i = max_i + 1; i < bank.length(); ++i) {
            if ((bank.at(i) - '0') > max2) {
                max2 = bank.at(i) - '0';
            }
        }
        total += max * 10 + max2;
    }

    return total;
}

std::uint64_t get_joltage2(const std::vector<std::string> &inputs) {
    std::uint64_t total{ 0 };
    for (const auto &bank : inputs) {
        std::string::size_type start_i{ 0 };
        std::uint64_t num = 0;
        for (int i = 11; i >= 0; --i) {
            int max{ bank.at(start_i) - '0' };
            for (std::string::size_type s = start_i + 1; s < bank.length() - i;
                 s++) {
                if ((bank.at(s) - '0') > max) {
                    max = bank.at(s) - '0';
                    start_i = s;
                }
            }
            start_i++;
            num += std::powl(10, i) * max;
        }
        total += num;
    }

    return total;
}

int main(int argc, const char **argv) {
    if (argc == 2) {
        auto inputs = get_inputs(argv[1]);
        std::println("{}", get_joltage(inputs));
        std::println("{}", get_joltage2(inputs));
    }
}
