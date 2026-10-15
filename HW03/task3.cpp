#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>

#include <omp.h>

#include "msort.h"

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: ./task3 n t ts" << std::endl;
        return 1;
    }
    std::size_t n = std::strtoull(argv[1], nullptr, 10);
    int t = std::atoi(argv[2]);
    std::size_t ts = std::strtoull(argv[3], nullptr, 10);

    // n random ints in [-1000, 1000]
    int *arr = new int[n];
    std::random_device entropy_source;
    std::mt19937 generator(entropy_source());
    std::uniform_int_distribution<int> dist(-1000, 1000);
    for (std::size_t i = 0; i < n; i++) {
        arr[i] = dist(generator);
    }

    omp_set_num_threads(t);

    high_resolution_clock::time_point start = high_resolution_clock::now();
    msort(arr, n, ts);
    high_resolution_clock::time_point end = high_resolution_clock::now();
    duration<double, std::milli> elapsed = duration_cast<duration<double, std::milli>>(end - start);

    std::cout << arr[0] << std::endl;
    std::cout << arr[n - 1] << std::endl;
    std::cout << elapsed.count() << std::endl;

    delete[] arr;
    return 0;
}
