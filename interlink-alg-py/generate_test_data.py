import random

def generate_alphabetical_ranges(n):
    alphabet = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
    random.shuffle(alphabet)
    ranges = []
    start_index = 0
    remaining_chars = len(alphabet)

    for i in range(n):
        max_size = remaining_chars - (3 * (n - i - 1))
        range_size = remaining_chars if i == n - 1 else random.randint(3, max_size)
        end_index = start_index + range_size
        ranges.append(alphabet[start_index:end_index])
        start_index = end_index
        remaining_chars -= range_size

    return ranges

def generate_random_word(range_chars):
    length = random.randint(1, 10)
    return ''.join(random.choice(range_chars) for _ in range(length))

def generate_test_data(sample_size):
    num_ranges = random.randint(1, 7)  # Randomize n to be a value between 1 and 7
    ranges = generate_alphabetical_ranges(num_ranges)
    interlinks = [generate_random_word(range_chars) for range_chars in ranges for _ in range(sample_size)]

    return ranges, interlinks
