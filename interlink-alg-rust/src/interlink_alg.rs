use fxhash::FxHashSet;
use fxhash::FxHashMap;

/// Traverse the chain of characters and identify elements.
/// Time Complexity: O(2C + C^2) where C is the number of unique characters in the alphabet
pub fn traverse_chain(
    sub_char: char,
    chars_set: &FxHashSet<char>,
    char_to_chars: &FxHashMap<char, FxHashSet<char>>,
    unravelled_elements: &mut FxHashSet<char>,
    element_identifier: &mut FxHashSet<char>,
) {
    if chars_set.iter().all(|&c| unravelled_elements.contains(&c)) || unravelled_elements.contains(&sub_char) {
        return;
    }

    for char in chars_set {
        element_identifier.insert(*char);
    }
    unravelled_elements.insert(sub_char);

    if let Some(sub_chars_set) = char_to_chars.get(&sub_char) {
        for sub_char_in_set in sub_chars_set {
            traverse_chain(*sub_char_in_set, sub_chars_set, char_to_chars, unravelled_elements, element_identifier);
        }
    }
}

/// Main function to interlink characters from the interlinks.
/// Time Complexity: O(M * L^2 + 2C + C^2) where M is the number of words, L is the average length of words,
/// and C is the number of unique characters in the alphabet.
pub fn interlink_alg(interlinks: &[String]) -> Vec<FxHashSet<char>> {
    // Step 1: Build char_to_chars map
    // Time Complexity: O(M * L^2) where M is the number of words and L is the average length of words
    let mut char_to_chars: FxHashMap<char, FxHashSet<char>> = FxHashMap::default();
    for word in interlinks {
        for char in word.chars() {
            let chars_set = char_to_chars.entry(char).or_insert_with(FxHashSet::default);
            for char_in_word in word.chars() {
                chars_set.insert(char_in_word);
            }
        }
    }

    let mut unravelled_elements = FxHashSet::default();
    let mut identifiers: Vec<FxHashSet<char>> = Vec::new();

    // Step 2: Traverse chains and identify elements
    // Time Complexity: O(2C + C^2) where C is the number of unique characters in the alphabet
    for (&char, chars_set) in &char_to_chars {
        if chars_set.iter().all(|&c| unravelled_elements.contains(&c)) {
            continue;
        }

        let mut element_identifier: FxHashSet<char> = chars_set.clone();

        for &c in chars_set {
            traverse_chain(c, &chars_set, &char_to_chars, &mut unravelled_elements, &mut element_identifier);
        }

        unravelled_elements.extend(chars_set);
        identifiers.push(element_identifier);
    }

    identifiers
}
