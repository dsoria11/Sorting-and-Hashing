import requests
import time

# Set target number of hashes
target_samples = 1000000
total_downloaded = 0

# Start prefix at 0 (which becomes "00000" in hex)
prefix_integer = 0

print(f"Starting download. Target: {target_samples:,} hashes...")

# Open the file in write mode
with open('million_hashes_only.txt', 'w') as outfile:
    # Keep looping and requesting until it hits the target amount
    while total_downloaded < target_samples:

        # Convert our integer into a 5-character uppercase hex string
        # (e.g., 0 -> "00000", 255 -> "000FF", 4095 -> "00FFF")
        prefix = f"{prefix_integer:05X}"

        url = f"https://api.pwnedpasswords.com/range/{prefix}"
        response = requests.get(url)

        if response.status_code == 200:
            lines = response.text.splitlines()

            # Process and write the batch to the file
            for line in lines:
                hash_suffix = line.split(':')[0]
                outfile.write(prefix + hash_suffix + '\n')

            # Update the running total
            total_downloaded += len(lines)

            # Print a status update every 50 requests so you know it isn't frozen
            if prefix_integer % 50 == 0:
                print(f"Prefix {prefix} complete. Total so far: {total_downloaded:,}")

            # Move to the next prefix for the next loop iteration
            prefix_integer += 1

        else:
            print(f"Network error on prefix {prefix}: Status {response.status_code}. Retrying in 2 seconds...")
            time.sleep(2)

print(f"\nSuccess! Finished downloading {total_downloaded:,} pure hashes to 'million_hashes_only.txt'.")