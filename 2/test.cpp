#include <print>
#include <string>

void check_str(const std::string &check) {
    char c = check.at(0);
    bool equal{ true };
    for (std::string::size_type i = 1; i < check.length(); i++) {
        if (check.at(i) != c) {
            equal = false;
            break;
        }
    }

    if (equal) {
        std::println("{} is good!", check);
        return;
    }

    // Next check if the digits make sense
    std::string::size_type next_c = check.find(c, 1);
    while (next_c <= check.length() / 2) {
        bool valid{ true };
        if (check.length() % next_c == 0) {
            // Check with this basis in mind
            for (std::string::size_type chunk = 1;
                 chunk < (check.length() / next_c); chunk++) {
                for (std::string::size_type inner = 0; inner < next_c;
                     inner++) {
                    if (check.at((chunk * next_c) + inner)
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
            std::println("{} is good!", check);
            break;
        }

        next_c = check.find(c, next_c + 1);
    }
}

int main() {
    check_str("884884884");
    check_str("111111111");
    check_str("2121212121");
    check_str("123412341234");
    check_str("1234512345");
    check_str("2121212118");
    check_str("123452345");
}
