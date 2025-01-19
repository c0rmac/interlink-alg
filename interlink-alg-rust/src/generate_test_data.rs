use rand::seq::SliceRandom;
use rand::Rng;

pub fn generate_alphabetical_ranges(n: usize) -> Vec<Vec<char>> {
    let mut alphabet: Vec<char> = ('A'..='Z').collect();
    let mut rng = rand::thread_rng();
    alphabet.shuffle(&mut rng);

    let mut ranges = Vec::new();
    let mut start_index = 0;
    let mut remaining_chars = alphabet.len();

    for i in 0..n {
        // Determine the size of the current range
        let max_size = remaining_chars - (3 * (n - i - 1));
        let range_size = if i == n - 1 {
            remaining_chars
        } else {
            rng.gen_range(3..=max_size)
        };

        let end_index = start_index + range_size;
        ranges.push(alphabet[start_index..end_index].to_vec());
        start_index = end_index;
        remaining_chars -= range_size;
    }

    ranges
}

pub fn generate_random_word(range: &[char]) -> String {
    let mut rng = rand::thread_rng();
    let length = rng.gen_range(1..=10);

    (0..length)
        .map(|_| range[rng.gen_range(0..range.len())])
        .collect()
}

pub fn generate_test_data(sample_size: usize) -> (Vec<Vec<char>>, Vec<String>) {
    let mut rng = rand::thread_rng();
    let num_ranges = rng.gen_range(1..=7); // Randomize n to be a value between 1 and 7

    let ranges = generate_alphabetical_ranges(num_ranges);
    let dictionary: Vec<String> = ranges.iter().flat_map(|range| (0..sample_size).map(move |_| generate_random_word(range))).collect();

    (ranges, dictionary)
}
