#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// To hold array and its size
typedef struct 
{
	int *array;
	size_t size; // m positions
} BloomArray;

// Allocating and initializing array to 0 (Modified for bit-packing: m/32)
BloomArray* create_array(size_t m) {
	BloomArray *ba = (BloomArray*)malloc(sizeof(BloomArray));
	if (ba == NULL) {
		return NULL; // Check for allocation failure
	}

	// Allocate enough integers to hold 'm' bits
	size_t num_ints = (m / 32) + 1;
	ba -> array = (int*)calloc(num_ints, sizeof(int));
	if (ba->array == NULL) {
		free(ba);
		return NULL;
	}

	ba->size = m;
	return ba;
}

// Extension: To reduce wasting memory for int allocation
// Set bit i to 1 using bitwise OR and left shift
void set_bit(BloomArray *ba, size_t i) {
	if (i < ba->size) {
		size_t array_index = i / 32;
		size_t bit_offset = i % 32;

		// Left shift a '1' to the correct offset and OR it with existing integer
		ba->array[array_index] |= (1 << bit_offset);
	}
}

// Check if bit i is 1 using bitwise AND and left shift
bool check_bit(BloomArray *ba, size_t i) {
	if (i < ba->size) {
		size_t array_index = i / 32;
		size_t bit_offset = i % 32;

		// Left shift a '1' to the offset, AND it, then check result is non-zero
		return (ba->array[array_index] & (1 << bit_offset)) != 0;
	}
	return false;
}

// Memory cleanup
void destroy_array(BloomArray *ba) {
	if (ba != NULL) {
		free(ba->array);
		free(ba);
	}
}

// To test it
int main() {
	// array that holds 100 bits
	BloomArray *myFilter = create_array(100);

	// set bit 42 to 1
	set_bit(myFilter, 42);

	// check if bit 42
	printf("Is bit 42 set? %d\n", check_bit(myFilter, 42));

	// check if bit 15 is 1 (true) -- should be false since rest are 0
	printf("Is bit 15 set? %d\n", check_bit(myFilter, 15));

	// to clean up
	destroy_array(myFilter);
	return 0;
}



