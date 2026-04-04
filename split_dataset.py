import random

def build_splits(input_file, train_size=900000):
    print(f"Loading hashes from {input_file}...")
    with open(input_file, 'r') as f:
        # Read lines and strip any trailing newline characters
        all_hashes = [line.strip() for line in f if line.strip()]

    total_hashes = len(all_hashes)
    print(f"Loaded {total_hashes:,} hashes.")

    # Shuffle the dataset
    print("Shuffling dataset...")
    random.shuffle(all_hashes)

    # Split the dataset
    # First 900k for Bloom Filter (positive)
    # Remainder for the false-positive check (negative)
    print(f"Splitting into {train_size:,} train and {total_hashes - train_size:,} test...")
    train_hashes = all_hashes[:train_size]
    test_hashes = all_hashes[train_size:]

    # Save the splits to separate files
    print("Saving splits to files...")
    with open('train_hashes.txt', 'w') as f:
        f.write('\n'.join(train_hashes))

    with open('test_hashes.txt', 'w') as f:
        f.write('\n'.join(test_hashes))

    print(f"-> 'train_hashes.txt' created ({len(train_hashes):,} hashes).")
    print(f"-> 'test_hashes.txt' created ({len(test_hashes):,} hashes).")

if __name__ == "__main__":
    build_splits('million_hashes_only.txt')