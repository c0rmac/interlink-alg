# InterlinkAlg
A colleague of mine presented me with the following issue from a collection of DNA codes.

Let a DNA code be denoted an alphabetic character. Suppose there is a dictionary containing a sequence of DNA codes. 
```python 
dictionary = ["A", "AB", "B", "BC", "C", "D", "CH", "E", "F", "EFG", "G", "FG", "H"]
```
Informally, we want to group together all DNA codes that corresponds with another code in the same sequence AS WELL as any 
other sequence in the dictionary. This will produce a set of sets called the identifiers set - a set of the different groups
that correspond with each other's code.

The result should be:
```python 
dictionary = [{'B', 'H', 'A', 'C'}, {'D'}, {'G', 'E', 'F'}]
```

## Formal Description

Let $\text{Alpha}$ be the alphabet and let $\text{Dict}$ be the dictionary.

Denote $\text{Seq}(y) \in \text{Dict}$ as any sequence that contains code $y$.

Define the equivalence relationship by $x \sim y \iff \exists \text{Seq}(y) : x \in \text{Seq}(y)$

Then the identifiers set is defined as:

$$
\text{Identifiers} = \text{Alpha} / \sim
$$

The objective is to find the members of the set $\text{Identifiers}$.

## Time Complexity

The overall time complexity of the algorithm is:

$$
O(M \times L^2 + 2C + C^2)
$$

Where:
-  $M = |\text{Dict }|$ is the number of words.
- $L$ is the average length of words.
- $C=|\text{Alpha }|$ is the number of unique characters in the alphabet.

## Algorithm Description
### 1. Initialize Data Structures:
- **CharMap (`char_to_chars`)**: A mapping that links each character to a set of other characters with which it has co-occurred in words.
- **Unravelled Elements (`unravelled_elements`)**: A set to keep track of characters that have been processed.
- **Identifiers (`identifiers`)**: A list to store sets of related characters that satisfy the equivalence relation.

### 2. Build the `char_to_chars` Map:

- **Input**: Dictionary.
- **Process**:
  - Iterate through each word in the dictionary.
  - For each character in the word, map it to all other characters in the same word.
  - This creates a graph-like structure where nodes are characters and edges represent co-occurrence in words.
- **Time Complexity**: $O(M \times L^2)$
  - Where $M$ is the number of words and $L$ is the average length of words.

### 3. Traverse Chains and Identify Elements:

- **Input**: The `char_to_chars` map.
- **Process**:
  - Initialize an empty set (`unravelled_elements`) to track processed characters.
  - Iterate through each character in the `char_to_chars` map.
  - For each unprocessed character, start a traversal to identify all related characters.
  - Recursively explore connected characters and add them to the current group (`element_identifier`).
  - Add the identified group of related characters to the final list of identifiers.
- **Time Complexity**: $O(2C + C^2)$
  - Where $C$ is the number of unique characters in the alphabet.

### 4. Return the Identified Groups:

- The algorithm returns a list of sets where each set contains characters that are related through the dataset of words.
