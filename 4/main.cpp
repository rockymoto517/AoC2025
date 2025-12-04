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

std::uint64_t get_papers(const std::vector<std::string> &inputs) {
    std::uint64_t papers{ 0 };
    for (std::size_t i = 0; i < inputs.size(); ++i) {
        for (std::size_t j = 0; j < inputs.at(i).length(); ++j) {
            if (inputs.at(i).at(j) == '@') {
                std::uint8_t paper_count{ 0 };
                if (i > 0) {
                    // Directly above
                    if (inputs.at(i - 1).at(j) == '@') {
                        paper_count++;
                    }
                    // Top left
                    if ((j > 0) && inputs.at(i - 1).at(j - 1) == '@') {
                        paper_count++;
                    }
                    // Top right
                    if ((j < (inputs.at(i - 1).length() - 1))
                        && inputs.at(i - 1).at(j + 1) == '@') {
                        paper_count++;
                    }
                }

                // Left
                if ((j > 0) && inputs.at(i).at(j - 1) == '@') {
                    paper_count++;
                }
                // Right
                if ((j < (inputs.at(i).length() - 1))
                    && inputs.at(i).at(j + 1) == '@') {
                    paper_count++;
                }

                if (i < (inputs.size() - 1)) {
                    // Directly below
                    if (inputs.at(i + 1).at(j) == '@') {
                        paper_count++;
                    }
                    // Bottom left
                    if ((j > 0) && inputs.at(i + 1).at(j - 1) == '@') {
                        paper_count++;
                    }
                    // Bottom right
                    if ((j < (inputs.at(i + 1).length() - 1))
                        && inputs.at(i + 1).at(j + 1) == '@') {
                        paper_count++;
                    }
                }

                if (paper_count < 4) {
                    papers++;
                }
            }
        }
    }

    return papers;
}

std::uint64_t get_papers2(const std::vector<std::string> &inputs) {
    std::uint64_t papers{ 0 };
    auto inputs_copy{ inputs };
    auto remove_papers = [&inputs_copy]() {
        std::uint64_t papers{ 0 };
        std::vector<std::string> new_inputs{};
        for (std::size_t i = 0; i < inputs_copy.size(); ++i) {
            std::string line{};
            for (std::size_t j = 0; j < inputs_copy.at(i).length(); ++j) {
                if (inputs_copy.at(i).at(j) == '@') {
                    std::uint8_t paper_count{ 0 };
                    if (i > 0) {
                        // Directly above
                        if (inputs_copy.at(i - 1).at(j) == '@') {
                            paper_count++;
                        }
                        // Top left
                        if ((j > 0)
                            && inputs_copy.at(i - 1).at(j - 1) == '@') {
                            paper_count++;
                        }
                        // Top right
                        if ((j < (inputs_copy.at(i - 1).length() - 1))
                            && inputs_copy.at(i - 1).at(j + 1) == '@') {
                            paper_count++;
                        }
                    }

                    // Left
                    if ((j > 0) && inputs_copy.at(i).at(j - 1) == '@') {
                        paper_count++;
                    }
                    // Right
                    if ((j < (inputs_copy.at(i).length() - 1))
                        && inputs_copy.at(i).at(j + 1) == '@') {
                        paper_count++;
                    }

                    if (i < (inputs_copy.size() - 1)) {
                        // Directly below
                        if (inputs_copy.at(i + 1).at(j) == '@') {
                            paper_count++;
                        }
                        // Bottom left
                        if ((j > 0)
                            && inputs_copy.at(i + 1).at(j - 1) == '@') {
                            paper_count++;
                        }
                        // Bottom right
                        if ((j < (inputs_copy.at(i + 1).length() - 1))
                            && inputs_copy.at(i + 1).at(j + 1) == '@') {
                            paper_count++;
                        }
                    }

                    if (paper_count < 4) {
                        line += '.';
                        papers++;
                    } else {
                        line += inputs_copy.at(i).at(j);
                    }
                } else {
                    line += '.';
                }
            }
            new_inputs.push_back(line);
        }

        inputs_copy = std::move(new_inputs);
        return papers;
    };

    std::uint64_t res = remove_papers();
    while (res > 0) {
        papers += res;
        res = remove_papers();
    }

    return papers;
}

int main(int argc, const char **argv) {
    if (argc == 2) {
        auto inputs = get_inputs(argv[1]);
        std::println("Part 1: {}", get_papers(inputs));
        std::println("Part 2: {}", get_papers2(inputs));
    }
}
