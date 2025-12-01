#include <cstdint>
#include <fstream>
#include <print>
#include <string>
#include <vector>

std::vector<std::string> get_inputs(const std::string &file) {
    std::ifstream f{ file };
    std::vector<std::string> result{};
    for (std::string line; std::getline(f, line);) {
        result.push_back(line);
    }

    return result;
}

std::vector<std::int32_t>
    get_rotations(const std::vector<std::string> &inputs) {
    std::vector<std::int32_t> rotations{};
    for (const auto &input : inputs) {
        if (input.at(0) == 'L') {
            rotations.push_back(-std::stoi(input.substr(1)));
        } else {
            rotations.push_back(std::stoi(input.substr(1)));
        }
    }

    return rotations;
}

std::uint64_t process_rotations(const std::vector<std::int32_t> &rotations) {
    std::int16_t dial{ 50 };
    std::uint64_t zeroes{ 0 };
    for (const auto rotation : rotations) {
        dial = (dial + rotation) % 100;
        if (dial == 0)
            zeroes++;
    }

    return zeroes;
}

std::uint64_t process_rotations2(const std::vector<std::int32_t> &rotations) {
    std::int16_t dial{ 50 };
    std::uint64_t zeroes{ 0 };
    for (const auto rotation : rotations) {
        zeroes += std::abs(rotation) / 100;
        std::int16_t next_dial = dial + (rotation % 100);
        if (dial != 0 && (next_dial <= 0 || next_dial > 99))
            zeroes++;

        dial = (((next_dial % 100) + 100) % 100);
    }

    return zeroes;
}

int main(int argc, const char **argv) {
    if (argc == 2) {
        auto rotations = get_rotations(get_inputs(argv[1]));
        std::uint64_t zeroes{ process_rotations(rotations) };
        std::print("\tPassword: {}\n", zeroes);

        std::uint64_t zeroes2{ process_rotations2(rotations) };
        std::print("\tPassword2: {}\n", zeroes2);
    }
}
