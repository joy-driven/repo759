#include "msort.h"

#include <algorithm>

// serial sort used once a piece is smaller than the threshold
static void insertion_sort(int *arr, std::size_t n) {
    for (std::size_t i = 1; i < n; i++) {
        int key = arr[i];
        std::size_t j = i;
        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;
    }
}

// merges the sorted halves arr[0, mid) and arr[mid, n) through tmp
static void merge(int *arr, int *tmp, std::size_t n, std::size_t mid) {
    std::merge(arr, arr + mid, arr + mid, arr + n, tmp);
    std::copy(tmp, tmp + n, arr);
}

// tmp is scratch space of the same length as arr
static void msort_rec(int *arr, int *tmp, std::size_t n, std::size_t threshold) {
    if (n < 2) {
        return;
    }
    if (n < threshold) {
        insertion_sort(arr, n);
        return;
    }

    std::size_t mid = n / 2;
#pragma omp task
    msort_rec(arr, tmp, mid, threshold);
#pragma omp task
    msort_rec(arr + mid, tmp + mid, n - mid, threshold);
#pragma omp taskwait

    merge(arr, tmp, n, mid);
}

void msort(int *arr, const std::size_t n, const std::size_t threshold) {
    int *tmp = new int[n];

    // one thread starts the recursion, the rest of the team picks up tasks
#pragma omp parallel
#pragma omp single
    msort_rec(arr, tmp, n, threshold);

    delete[] tmp;
}
