#include "generate_test_data.hpp"
#include "interlink_alg.hpp"
#include <iostream>
#include <chrono>

int main() {
    int sample_size = 120000; // You can change this value to adjust the sample size per range

    auto start_time = std::chrono::high_resolution_clock::now();
    auto [ranges, interlinks] = generate_test_data(sample_size);

    // Print ranges for verification
    for (size_t i = 0; i < ranges.size(); ++i) {
        std::cout << "Range " << i + 1 << ": ";
        for (char c : ranges[i]) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }

    auto interlink_start_time = std::chrono::high_resolution_clock::now(); // Start timing the algorithm
    auto identifiers = interlink_alg(interlinks);
    auto interlink_end_time = std::chrono::high_resolution_clock::now(); // End timing the algorithm

    auto interlink_execution_time = std::chrono::duration<double>(interlink_end_time - interlink_start_time).count();
    std::cout << "Execution time of InterlinkAlg: " << interlink_execution_time << " seconds" << std::endl;

    std::vector<std::vector<char>> ordered_identifiers;
    for (const auto& id_set : identifiers) {
        std::vector<char> id_vec(id_set.begin(), id_set.end());
        std::sort(id_vec.begin(), id_vec.end());
        ordered_identifiers.push_back(id_vec);
    }

    // Assert that the lengths of ranges and identifiers are the same
    if (ranges.size() != ordered_identifiers.size()) {
        std::cerr << "The lengths of ranges and identifiers do not match" << std::endl;
        return 1;
    }

    // Assert that identifiers coincide with the ranges
    for (const auto& range : ranges) {
        std::vector<char> range_sorted = range;
        std::sort(range_sorted.begin(), range_sorted.end());
        if (std::find(ordered_identifiers.begin(), ordered_identifiers.end(), range_sorted) == ordered_identifiers.end()) {
            std::cerr << "Identifier ";
            for (char c : range_sorted) {
                std::cerr << c;
            }
            std::cerr << " not found in ranges" << std::endl;
            return 1;
        }
    }

    for (const auto& id_vec : ordered_identifiers) {
        for (char c : id_vec) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }

    auto total_end_time = std::chrono::high_resolution_clock::now();
    auto total_execution_time = std::chrono::duration<double>(total_end_time - start_time).count();
    std::cout << "Total execution time: " << total_execution_time << " seconds" << std::endl;

    return 0;
}
