#include <stdio.h>
#include <string.h>
#include <time.h>

// Colin Welter
// To use this code in another file put #include hash.c
// use the function get hases it fills the array indicies with values

// Hash functions 

// djb2
unsigned long hash1(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

// sdbm
unsigned long hash2(const char *str) {
    unsigned long hash = 0;
    int c;

    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}


void getHashes(const char *key, int k, int m, int indices[]) {
    unsigned long h1 = hash1(key);
    unsigned long h2 = hash2(key);

    for (int i = 0; i < k; i++) {
        indices[i] = (int)(h1 + i * h2) % m;

        if (indices[i] < 0)
            indices[i] += m;
    }
}

