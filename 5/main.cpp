#include <fstream>
#include <print>
#include <string>
#include <utility>
#include <vector>

using id_range = std::pair<std::uint64_t, std::uint64_t>;

std::pair<std::vector<id_range>, std::vector<std::uint64_t>>
    get_inputs(const std::string &file) {
    std::ifstream f{ file };
    std::vector<id_range> fresh_ids{};
    for (std::string line; std::getline(f, line);) {
        if (line.size() == 0)
            break;

        std::string::size_type mid = line.find('-');
        fresh_ids.push_back({ std::stoull(line.substr(0, mid)),
                              std::stoull(line.substr(mid + 1)) });
    }

    std::vector<std::uint64_t> items{};
    for (std::string line; std::getline(f, line);) {
        items.push_back(std::stoull(line));
    }

    return { fresh_ids, items };
}

std::uint64_t get_fresh(const std::vector<id_range> &fresh_ids,
                        const std::vector<std::uint64_t> &items) {
    std::uint64_t fresh{ 0 };

    for (const auto item : items) {
        bool bad{ true };
        for (const auto &[min, max] : fresh_ids) {
            if (item >= min && item <= max) {
                bad = false;
                break;
            }
        }

        if (!bad)
            fresh++;
    }

    return fresh;
}

std::uint64_t get_fresh2(const std::vector<id_range> &fresh_ids) {
    std::uint64_t fresh{ 0 };

    std::vector<id_range> remove_subsets{};
    for (const auto &[min, max] : fresh_ids) {
        bool bad{ false };
        for (auto &[min2, max2] : remove_subsets) {
            if (min2 <= min && max2 >= max) {
                bad = true;
                break;
            } else if (min <= min2 && max >= max2) {
                min2 = min;
                max2 = max;
                bad = true;
                break;
            }
        }

        if (!bad) {
            remove_subsets.push_back({ min, max });
        }
    }

    for (std::size_t i{ 0 }; i < remove_subsets.size(); ++i) {
        auto [min, max] = remove_subsets.at(i);
        bool subset{ false };
        for (std::size_t j{ 0 }; j < i; ++j) {
            const auto [min2, max2] = remove_subsets.at(j);
            if (min >= min2 && min <= max2) {
                // We're a subset
                if (max <= max2) {
                    subset = true;
                    break;
                } else {
                    min = max2 + 1;
                }
            }

            if (max <= max2 && max >= min2) {
                // We're a subset
                if (min >= min2) {
                    subset = true;
                    break;
                } else {
                    max = min2 - 1;
                }
            }
        }

        if (!subset) {
            fresh += max - min + 1;
        }
    }

    return fresh;
}

int main(int argc, const char **argv) {
    if (argc == 2) {
        auto [fresh_ids, items] = get_inputs(argv[1]);
        std::println("get_fresh1: {}", get_fresh(fresh_ids, items));
        std::println("get_fresh2: {}", get_fresh2(fresh_ids));
    }
}
