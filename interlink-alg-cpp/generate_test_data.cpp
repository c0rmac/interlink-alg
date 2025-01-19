#include "generate_test_data.hpp"
#include <algorithm>
#include <random>
#include <chrono>

std::vector<std::vector<char>> generate_alphabetical_ranges(int n) {
    std::vector<char> alphabet;
    for (char c = 'A'; c <= 'Z'; ++c) {
        alphabet.push_back(c);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(alphabet.begin(), alphabet.end(), g);

    std::vector<std::vector<char>> ranges;
    int start_index = 0;
    int remaining_chars = alphabet.size();

    for (int i = 0; i < n; ++i) {
        int max_size = remaining_chars - (3 * (n - i - 1));
        std::uniform_int_distribution<int> dist(3, max_size);
        int range_size = (i == n - 1) ? remaining_chars : dist(g);
        std::vector<char> range(alphabet.begin() + start_index, alphabet.begin() + start_index + range_size);
        ranges.push_back(range);
        start_index += range_size;
        remaining_chars -= range_size;
    }

    return ranges;
}

std::string generate_random_word(const std::vector<char>& range) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> length_dist(1, 10);

    int length = length_dist(g);
    std::string word;

    std::uniform_int_distribution<int> char_dist(0, range.size() - 1);
    for (int i = 0; i < length; ++i) {
        word += range[char_dist(g)];
    }

    return word;
}

std::pair<std::vector<std::vector<char>>, std::vector<std::string>> generate_test_data(int sample_size) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> range_dist(1, 7);

    int num_ranges = range_dist(g);
    auto ranges = generate_alphabetical_ranges(num_ranges);
    std::vector<std::string> interlinks;

    for (const auto& range : ranges) {
        for (int i = 0; i < sample_size; ++i) {
            interlinks.push_back(generate_random_word(range));
        }
    }

    return {ranges, interlinks};
}
