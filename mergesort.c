#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merge three sorted subarrays: [left...mid1], [mid1+1...mid2], [mid2+1...right]
void merge3(int arr[], int left, int mid1, int mid2, int right) {
    int n1 = mid1 - left + 1;
    int n2 = mid2 - mid1;
    int n3 = right - mid2;

    int *A = malloc(n1 * sizeof(int));
    int *B = malloc(n2 * sizeof(int));
    int *C = malloc(n3 * sizeof(int));

    // Error checking for malloc
    if (!A || !B || !C) {
        printf("Memory allocation failed in merge!\n");
        exit(1);
    }

    for (int i = 0; i < n1; i++) A[i] = arr[left + i];
    for (int i = 0; i < n2; i++) B[i] = arr[mid1 + 1 + i];
    for (int i = 0; i < n3; i++) C[i] = arr[mid2 + 1 + i];

    int i = 0, j = 0, k = 0, l = left;

    // 1. Merge three arrays while all have elements
    while (i < n1 && j < n2 && k < n3) {
        if (A[i] <= B[j] && A[i] <= C[k])
            arr[l++] = A[i++];
        else if (B[j] <= A[i] && B[j] <= C[k])
            arr[l++] = B[j++];
        else
            arr[l++] = C[k++];
    }

    // 2. Merge remaining two arrays (when one is exhausted)
    while (i < n1 && j < n2) arr[l++] = (A[i] <= B[j]) ? A[i++] : B[j++];
    while (j < n2 && k < n3) arr[l++] = (B[j] <= C[k]) ? B[j++] : C[k++];
    while (i < n1 && k < n3) arr[l++] = (A[i] <= C[k]) ? A[i++] : C[k++];

    // 3. Copy any remaining elements (when two are exhausted)
    while (i < n1) arr[l++] = A[i++];
    while (j < n2) arr[l++] = B[j++];
    while (k < n3) arr[l++] = C[k++];

    free(A);
    free(B);
    free(C);
}

void mergeSort3(int arr[], int left, int right) {
    // Base case: if range has 1 or 0 elements
    if (left >= right) return;

    // Simplified Partitioning
    int mid1 = left + (right - left) / 3;
    int mid2 = left + 2 * (right - left) / 3;

    // Ensure mid2 is actually after mid1 for small arrays
    if (mid2 <= mid1) mid2 = mid1 + 1; 
    // Bounds check to ensure we don't exceed 'right'
    if (mid2 >= right) mid2 = right - 1;

    // Recursively sort the 3 parts
    mergeSort3(arr, left, mid1);
    mergeSort3(arr, mid1 + 1, mid2);
    mergeSort3(arr, mid2 + 1, right);

    // Merge the 3 sorted parts
    merge3(arr, left, mid1, mid2, right);
}

int isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        if (arr[i] > arr[i + 1]) return 0;
    return 1;
}

int main() {
    int n;
    srand(time(NULL)); // Seed the randomizer

    printf("Enter size of array: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    int *arr = malloc(n * sizeof(int));
    if (!arr) return 1;

    for (int i = 0; i < n; i++) arr[i] = rand() % 100;

    if (n <= 20) {
        printf("Before: ");
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
    }

    clock_t start = clock();
    mergeSort3(arr, 0, n - 1);
    clock_t end = clock();

    printf("Time: %.2f ms\n", (double)(end - start) * 1000.0 / CLOCKS_PER_SEC);

    if (n <= 20) {
        printf("After:  ");
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
    }

    printf("%s\n", isSorted(arr, n) ? "Sorting successful!" : "Sorting failed!");

    free(arr);
    return 0;
}
