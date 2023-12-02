#include "trebuchet.hpp"

int trebuchetDigits(std::string input_file) {
    std::ifstream input_stream(input_file);
    std::string   line;

    uint32_t sum = 0;
    while (std::getline(input_stream, line)) {
        auto l_it = std::find_if(line.begin(), line.end(), ::isdigit);
        auto r_it = std::find_if(line.rbegin(), line.rend(), ::isdigit);

        std::string number;
        number.push_back(*l_it);
        number.push_back(*r_it);

        sum += std::stoi(number);
    }
    return sum;
}

int trebuchetNames(std::string input_file) {
    static std::unordered_map<std::string, uint8_t> digit_names = {{"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
                                                                   {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

    std::ifstream input_stream(input_file);
    std::string   line;

    uint32_t sum = 0;

    while (std::getline(input_stream, line)) {
        auto closest_n_left  = std::find_if(line.begin(), line.end(), ::isdigit);
        auto closest_n_right = std::find_if(line.rbegin(), line.rend(), ::isdigit);

        std::string l_substr(line.begin(), closest_n_left);
        std::string l_name;
        size_t      current_n_left;

        std::string r_substr(line.rbegin(), closest_n_right);
        std::string r_name;
        size_t      current_n_right;

        // Searching from the left side
        for (auto [name, digit] : digit_names) {
            current_n_left = l_substr.find(name, 0);
            if (current_n_left == std::string::npos) {
                continue;
            }
            if (std::distance(line.begin(), closest_n_left) > std::distance(line.begin(), line.begin() + current_n_left)) {
                closest_n_left = line.begin() + current_n_left;

                l_name = name;
            }
        }
        // Searching from the right side
        for (auto [name, digit] : digit_names) {
            std::string reversed_name = name;
            std::reverse(reversed_name.begin(), reversed_name.end());
            current_n_right = r_substr.find(reversed_name, 0);
            if (current_n_right == std::string::npos) {
                continue;
            }
            if (std::distance(line.rbegin(), closest_n_right) > std::distance(line.rbegin(), line.rbegin() + current_n_right)) {
                closest_n_right = line.rbegin() + current_n_right;

                r_name = name;
            }
        }

        std::string number;
        if (!l_name.empty()) {
            number.append(std::to_string(digit_names.at(l_name)));
        } else {
            number.push_back(*closest_n_left);
        }
        if (!r_name.empty()) {
            number.append(std::to_string(digit_names.at(r_name)));
        } else {
            number.push_back(*closest_n_right);
        }
        sum += std::stoi(number);
    }
    return sum;
}