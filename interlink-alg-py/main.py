import time
from generate_test_data import generate_test_data
from interlink_alg import interlink_alg

def main():
    sample_size = 6000  # You can change this value to adjust the sample size per range

    # Generate test data
    start_time = time.time()
    ranges, interlinks = generate_test_data(sample_size)

    # Print ranges for verification
    for i, range_chars in enumerate(ranges):
        print(f"Range {i + 1}: {range_chars}")

    interlink_start_time = time.time()  # Start timing the algorithm
    identifiers = interlink_alg(interlinks)
    interlink_end_time = time.time()  # End timing the algorithm

    interlink_execution_time = interlink_end_time - interlink_start_time
    print(f"Execution time of InterlinkAlg: {interlink_execution_time} seconds")

    ordered_identifiers = [sorted(list(id_set)) for id_set in identifiers]

    # Assert that the lengths of ranges and identifiers are the same
    assert len(ranges) == len(ordered_identifiers), "The lengths of ranges and identifiers do not match"

    # Assert that identifiers coincide with the ranges
    for range_chars in ranges:
        range_sorted = sorted(range_chars)
        assert range_sorted in ordered_identifiers, f"Identifier {range_sorted} not found in ranges"

    print(ordered_identifiers)

    total_end_time = time.time()
    total_execution_time = total_end_time - start_time
    print(f"Total execution time: {total_execution_time} seconds")

if __name__ == "__main__":
    main()
