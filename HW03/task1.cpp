#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>

#include <omp.h>

#include "matmul.h"

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: ./task1 n t" << std::endl;
        return 1;
    }
    std::size_t n = std::strtoull(argv[1], nullptr, 10);
    int t = std::atoi(argv[2]);

    // n x n matrices with random floats in [-1, 1], same as HW02 task3
    float *A = new float[n * n];
    float *B = new float[n * n];
    float *C = new float[n * n];

    std::random_device entropy_source;
    std::mt19937 generator(entropy_source());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    for (std::size_t i = 0; i < n * n; i++) {
        A[i] = dist(generator);
        B[i] = dist(generator);
    }

    omp_set_num_threads(t);

    high_resolution_clock::time_point start = high_resolution_clock::now();
    mmul(A, B, C, n);
    high_resolution_clock::time_point end = high_resolution_clock::now();
    duration<double, std::milli> elapsed = duration_cast<duration<double, std::milli>>(end - start);

    std::cout << C[0] << std::endl;
    std::cout << C[n * n - 1] << std::endl;
    std::cout << elapsed.count() << std::endl;

    delete[] A;
    delete[] B;
    delete[] C;
    return 0;
}
