#include <iostream>
#include <sstream>
#include <unordered_map>

#include "cube_conundrum.hpp"

enum CubeLimit {
    RED   = 12,
    GREEN = 13,
    BLUE  = 14,
};

uint32_t possible_games(std::string input_path) {
    std::ifstream input_stream(input_path);
    std::string   line;
    int           game_no     = 0;
    int           sum_game_no = 0;
    int           cube_qty;
    std::string   cube_color;

    while (std::getline(input_stream, line)) {
        bool legal   = true;
        int  sum_red = 0, sum_green = 0, sum_blue = 0;

        std::string       word;
        std::stringstream ss(line);

        game_no++;
        std::getline(ss, word, ' ');
        std::getline(ss, word, ' ');  // skip Game #
        while (std::getline(ss, word, ' ')) {
            cube_qty = std::stoi(word);
            std::getline(ss, word, ' ');
            cube_color = word;
            if (cube_color[0] == 'r') {
                sum_red += cube_qty;
            } else if (cube_color[0] == 'g') {
                sum_green += cube_qty;
            } else {
                sum_blue += cube_qty;
            }
            if (cube_color.back() == ';') {
                if (sum_red > CubeLimit::RED || sum_green > CubeLimit::GREEN || sum_blue > CubeLimit::BLUE) {
                    break;
                }
                sum_red = 0, sum_green = 0, sum_blue = 0;
            }
        }
        if (sum_red <= CubeLimit::RED && sum_green <= CubeLimit::GREEN && sum_blue <= CubeLimit::BLUE) {
            sum_game_no += game_no;
        }
    }

    return sum_game_no;
}
uint32_t fewest_cubes(std::string input_file) {
    std::fstream input_stream(input_file);
    std::string  line;

    uint32_t product_sum = 0;

    int sum_red = 0, sum_green = 0, sum_blue = 0;

    while (std::getline(input_stream, line)) {
        std::unordered_map<char, uint32_t> color_map = {{'r', 0}, {'g', 0}, {'b', 0}};
        std::stringstream                  ss(line);
        std::string                        word;

        uint32_t cube_qty;
        char     cube_color;

        std::getline(ss, word, ' ');
        std::getline(ss, word, ' ');  // skip Game #
        while (std::getline(ss, word, ' ')) {
            cube_qty = std::stoi(word);
            std::getline(ss, word, ' ');
            cube_color = word[0];
            if (cube_color == 'r' && cube_qty > color_map.at('r')) {
                color_map.at('r') = cube_qty;
            } else if (cube_color == 'g' && cube_qty > color_map.at('g')) {
                color_map.at('g') = cube_qty;
            } else if (cube_color == 'b' && cube_qty > color_map.at('b')) {
                color_map.at('b') = cube_qty;
            }
        }
        uint32_t product = 1;
        for (auto [color, qty] : color_map) {
            product *= qty;
        }
        product_sum += product;
    }
    return product_sum;
}