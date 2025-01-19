#include "interlink_alg.hpp"

void traverse_chain(
        char sub_char,
        const CharSet& chars_set,
        const CharMap& char_to_chars,
        CharSet& unravelled_elements,
        CharSet& element_identifier
) {
    if (std::all_of(chars_set.begin(), chars_set.end(), [&unravelled_elements](char c) { return unravelled_elements.count(c) > 0; }) || unravelled_elements.count(sub_char) > 0) {
        return;
    }

    element_identifier.insert(chars_set.begin(), chars_set.end());
    unravelled_elements.insert(sub_char);

    auto it = char_to_chars.find(sub_char);
    if (it != char_to_chars.end()) {
        for (char sub_char_in_set : it->second) {
            traverse_chain(sub_char_in_set, it->second, char_to_chars, unravelled_elements, element_identifier);
        }
    }
}

std::vector<CharSet> interlink_alg(const std::vector<std::string>& interlinks) {
    // Step 1: Build char_to_chars map
    // Time Complexity: O(M * L^2) where M is the number of words and L is the average length of words
    CharMap char_to_chars;
    for (const auto& word : interlinks) {
        for (char c : word) {
            CharSet& chars_set = char_to_chars[c];
            for (char c_in_word : word) {
                chars_set.insert(c_in_word);
            }
        }
    }

    CharSet unravelled_elements;
    std::vector<CharSet> identifiers;

    // Step 2: Traverse chains and identify elements
    // Time Complexity: O(2C + C^2) where C is the number of unique characters in the alphabet
    for (const auto& [char_key, chars_set] : char_to_chars) {
        if (std::all_of(chars_set.begin(), chars_set.end(), [&unravelled_elements](char c) { return unravelled_elements.count(c) > 0; })) {
            continue;
        }

        CharSet element_identifier = chars_set;

        for (char c : chars_set) {
            traverse_chain(c, chars_set, char_to_chars, unravelled_elements, element_identifier);
        }

        unravelled_elements.insert(chars_set.begin(), chars_set.end());
        identifiers.push_back(element_identifier);
    }

    return identifiers;
}
