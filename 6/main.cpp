#include <cctype>
#include <fstream>
#include <print>
#include <string>
#include <vector>

// Returns {
//	numbers - col, row;
//	operations
// }
std::pair<std::vector<std::vector<std::uint64_t>>, std::vector<bool>>
    get_inputs(const std::string &file) {
    std::ifstream f{ file };

    std::vector<std::vector<std::uint64_t>> inputs{};
    std::string operators_line{};
    for (std::string line; std::getline(f, line);) {
        std::uint64_t col{ 0 };
        for (std::size_t i = 0; i < line.size(); ++i) {
            if (line.at(i) == '*' || line.at(i) == '+') {
                operators_line = line;
                break;
            }

            // Skip whitespace
            while (i < line.size() && std::isspace(line.at(i)))
                ++i;

            std::uint64_t num{ 0 };
            while (i < line.size() && std::isdigit(line.at(i))) {
                num = num * 10 + (line.at(i) - '0');
                ++i;
            }

            if (num > 0) {
                if (inputs.size() <= col)
                    inputs.push_back(std::vector<std::uint64_t>{});

                inputs.at(col).push_back(num);
                col++;
            }
        }
    }

    std::vector<bool> operators{};
    for (std::size_t i = 0; i < operators_line.size(); ++i) {
        // Skip whitespace
        while (i < operators_line.size() && std::isspace(operators_line.at(i)))
            ++i;

        if (i >= operators_line.size())
            break;
        else if (operators_line.at(i) == '*')
            operators.push_back(true);
        else if (operators_line.at(i) == '+')
            operators.push_back(false);
    }

    return { inputs, operators };
}

std::uint64_t
    solve_worksheet(const std::vector<std::vector<std::uint64_t>> &inputs,
                    const std::vector<bool> &operations) {
    std::uint64_t total{ 0 };

    for (std::size_t i = 0; i < inputs.size(); ++i) {
        std::uint64_t cur{ 0 };
        // use mul identity instead of add identity
        if (operations.at(i))
            cur++;
        for (std::size_t j = 0; j < inputs.at(i).size(); ++j) {
            if (operations.at(i)) {
                cur *= inputs.at(i).at(j);
            } else {
                cur += inputs.at(i).at(j);
            }
        }
        total += cur;
    }

    return total;
}

std::pair<std::vector<std::string>, std::vector<bool>>
    get_inputs2(const std::string &file) {
    std::ifstream f{ file };

    std::vector<std::string> inputs{};
    std::string operators_line{};
    for (std::string line; std::getline(f, line);) {
        if (line.find('*') != std::string::npos) {
            operators_line = line;
            break;
        }
        inputs.push_back(line);
    }

    std::vector<bool> operators{};
    for (std::size_t i = 0; i < operators_line.size(); ++i) {
        // Skip whitespace
        while (i < operators_line.size() && std::isspace(operators_line.at(i)))
            ++i;

        if (i >= operators_line.size())
            break;
        else if (operators_line.at(i) == '*')
            operators.push_back(true);
        else if (operators_line.at(i) == '+')
            operators.push_back(false);
    }

    return { inputs, operators };
}

std::uint64_t solve_worksheet2(const std::vector<std::string> &inputs,
                               const std::vector<bool> &operators) {
    std::uint64_t total{ 0 };

    std::size_t line_length{ inputs.at(0).size() };
    std::uint64_t addend{ 0 };
    std::uint64_t operator_idx{ 0 };
    for (std::size_t i = 0; i < line_length; ++i) {
        // Use mul identity over add identity
        if (operators.at(operator_idx) && addend == 0)
            addend = 1;

        std::uint64_t num{ 0 };
        bool empty{ true };
        for (const auto &line : inputs) {
            if (std::isdigit(line.at(i))) {
                num = num * 10 + (line.at(i) - '0');
                empty = false;
            }
        }

        if (operators.at(operator_idx) && num > 0) {
            addend *= num;
        } else
            addend += num;

        if (empty || i == line_length - 1) {
            total += addend;
            addend = 0;
            operator_idx++;
            continue;
        }
    }

    return total;
}

int main(int argc, const char **argv) {
    if (argc == 2) {
        auto [inputs, operations] = get_inputs(argv[1]);
        std::println("Solve Worksheet {}",
                     solve_worksheet(inputs, operations));
        auto [inputs2, operations2] = get_inputs2(argv[1]);
        std::println("Solve Worksheet2 {}",
                     solve_worksheet2(inputs2, operations2));
    }
}
