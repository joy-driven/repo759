#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>

#include "scan.h"

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./task1 n" << std::endl;
        return 1;
    }
    std::size_t n = std::strtoull(argv[1], nullptr, 10);

    // n random floats in [-1, 1]
    float *arr = new float[n];
    float *output = new float[n];

    std::random_device entropy_source;
    std::mt19937 generator(entropy_source());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    for (std::size_t i = 0; i < n; i++) {
        arr[i] = dist(generator);
    }

    // time the scan
    high_resolution_clock::time_point start = high_resolution_clock::now();
    scan(arr, output, n);
    high_resolution_clock::time_point end = high_resolution_clock::now();
    duration<double, std::milli> elapsed = duration_cast<duration<double, std::milli>>(end - start);

    std::cout << elapsed.count() << std::endl;
    std::cout << output[0] << std::endl;
    std::cout << output[n - 1] << std::endl;

    delete[] arr;
    delete[] output;
    return 0;
}
