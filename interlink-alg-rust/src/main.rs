mod generate_test_data;
mod interlink_alg;

use generate_test_data::{generate_test_data};
use interlink_alg::interlink_alg;
use std::time::Instant;

fn main() {
    let sample_size = 12_00000; // You can change this value to adjust the sample size per range

    let start_time = Instant::now();
    let (ranges, dictionary) = generate_test_data(sample_size);

    // Print ranges for verification
    for (i, range) in ranges.iter().enumerate() {
        println!("Range {}: {:?}", i + 1, range);
    }

    let interlink_start_time = Instant::now(); // Start timing the algorithm
    let identifiers = interlink_alg(&dictionary);
    let interlink_end_time = Instant::now(); // End timing the algorithm

    let interlink_execution_time = interlink_end_time.duration_since(interlink_start_time).as_secs_f64();
    println!("Execution time of InterlinkAlg: {} seconds", interlink_execution_time);

    let ordered_identifiers: Vec<Vec<char>> = identifiers.iter().map(|id| {
        let mut id_vec: Vec<char> = id.iter().cloned().collect();
        id_vec.sort();
        id_vec
    }).collect();

    // Assert that the lengths of ranges and identifiers are the same
    assert_eq!(ranges.len(), ordered_identifiers.len(), "The lengths of ranges and identifiers do not match");

    // Assert that identifiers coincide with the ranges
    for range in &ranges {
        let range_sorted: Vec<char> = {
            let mut temp = range.clone();
            temp.sort();
            temp
        };
        assert!(ordered_identifiers.contains(&range_sorted), "Identifier {:?} not found in ranges", range_sorted);
    }

    println!("{:?}", ordered_identifiers);

    let total_end_time = Instant::now();
    let total_execution_time = total_end_time.duration_since(start_time).as_secs_f64();
    println!("Total execution time: {} seconds", total_execution_time);
}
