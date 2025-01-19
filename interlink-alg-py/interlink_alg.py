from collections import defaultdict

def traverse_chain(sub_char, chars_set, char_to_chars, unravelled_elements, element_identifier):
    if all(c in unravelled_elements for c in chars_set) or sub_char in unravelled_elements:
        return

    for char in chars_set:
        element_identifier.add(char)
    unravelled_elements.add(sub_char)

    if sub_char in char_to_chars:
        sub_chars_set = char_to_chars[sub_char]
        for sub_char_in_set in sub_chars_set:
            traverse_chain(sub_char_in_set, sub_chars_set, char_to_chars, unravelled_elements, element_identifier)

def interlink_alg(interlinks):
    # Step 1: Build char_to_chars map
    # Time Complexity: O(M * L^2) where M is the number of words and L is the average length of words
    char_to_chars = defaultdict(set)
    for word in interlinks:
        for char in word:
            chars_set = char_to_chars[char]
            for char_in_word in word:
                chars_set.add(char_in_word)

    unravelled_elements = set()
    identifiers = []

    # Step 2: Traverse chains and identify elements
    # Time Complexity: O(2C + C^2) where C is the number of unique characters in the alphabet
    for char, chars_set in char_to_chars.items():
        if all(c in unravelled_elements for c in chars_set):
            continue

        element_identifier = set(chars_set)

        for c in chars_set:
            traverse_chain(c, chars_set, char_to_chars, unravelled_elements, element_identifier)

        unravelled_elements.update(chars_set)
        identifiers.append(element_identifier)

    return identifiers
