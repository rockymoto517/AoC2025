#include <cctype>
#include <cstdint>
#include <fstream>
#include <print>
#include <string>
#include <utility>
#include <vector>

using id_range = std::pair<std::uint64_t, std::uint64_t>;

std::vector<id_range> get_inputs(const std::string &file) {
    std::ifstream f{ file };
    std::string input{};
    std::getline(f, input);

    std::vector<id_range> inputs{};

    // mini parser :D
    // state:
    bool end_range{ false };
    std::string first{};
    std::string second{};
    for (const auto c : input) {
        if (std::isdigit(c)) {
            if (end_range) {
                second += c;
            } else {
                first += c;
            }
        } else if (c == '-') {
            end_range = true;
        } else if (c == ',') {
            end_range = false;
            inputs.push_back({ std::stoll(first), std::stoll(second) });
            first.clear();
            second.clear();
        } else {
            std::println("Invalid token: {{}}", c);
        }
    }
    inputs.push_back({ std::stoi(first), std::stoi(second) });
    first.clear();
    second.clear();

    return inputs;
}

std::uint64_t find_dupes(const std::vector<id_range> &inputs) {
    std::uint64_t password{ 0 };
    for (const auto &range : inputs) {
        for (std::uint64_t i = std::get<0>(range); i <= std::get<1>(range);
             i++) {
            std::string check{ std::to_string(i) };
            if (check.length() % 2 != 0)
                continue;

            bool bad{ false };
            for (std::string::size_type s1 = 0, s2 = check.length() / 2;
                 s2 < check.length(); s1++, s2++) {
                if (check.at(s1) != check.at(s2)) {
                    bad = true;
                    break;
                }
            }
            if (!bad) {
                password += i;
            }
        }
    }

    return password;
}

std::uint64_t find_dupes2(const std::vector<id_range> &inputs) {
    std::uint64_t password{ 0 };
    for (const auto &range : inputs) {
        for (std::uint64_t i = std::get<0>(range); i <= std::get<1>(range);
             i++) {
            if (i < 11)
                continue;

            std::string check{ std::to_string(i) };

            char c = check.at(0);
            bool equal{ true };
            // Check if we're a string of the same digit
            for (std::string::size_type i = 1; i < check.length(); i++) {
                if (check.at(i) != c) {
                    equal = false;
                    break;
                }
            }
            if (equal) {
                password += i;
                continue;
            }

            // Next check if the digits make sense
            std::string::size_type next_c = check.find(c, 1);
            while (next_c <= check.length() / 2) {
                bool valid{ true };
                if (check.length() % next_c == 0) {
                    // Check with this basis in mind
                    for (std::string::size_type chunk = 1;
                         chunk < check.length() / next_c; chunk++) {
                        for (std::string::size_type inner = 0; inner < next_c;
                             inner++) {
                            if (check.at(chunk * next_c + inner)
                                != check.at(inner)) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid)
                            break;
                    }
                } else {
                    valid = false;
                }

                if (valid) {
                    password += i;
                    break;
                }

                next_c = check.find(c, next_c + 1);
            }
        }
    }

    return password;
}

int main(int argc, const char **argv) {
    if (argc == 2) {
        auto inputs = get_inputs(argv[1]);
        std::println("{}", find_dupes(inputs));
        std::println("{}", find_dupes2(inputs));
    }
}
