#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using CharSet = std::unordered_set<char>;
using CharMap = std::unordered_map<char, CharSet>;

void traverse_chain(
        char sub_char,
        const CharSet& chars_set,
        const CharMap& char_to_chars,
        CharSet& unravelled_elements,
        CharSet& element_identifier
);

std::vector<CharSet> interlink_alg(const std::vector<std::string>& interlinks);
