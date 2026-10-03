#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include "matmul.h"

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

int main() {
    const unsigned int n = 1024;

    // A and B are kept as vectors for mmul4; A.data() and B.data()
    // give the same matrices as raw row-major arrays for mmul1-3
    std::vector<double> A(n * n);
    std::vector<double> B(n * n);
    double *C = new double[n * n];

    std::random_device entropy_source;
    std::mt19937 generator(entropy_source());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    for (unsigned int i = 0; i < n * n; i++) {
        A[i] = dist(generator);
        B[i] = dist(generator);
    }

    std::cout << n << std::endl;

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> elapsed;

    start = high_resolution_clock::now();
    mmul1(A.data(), B.data(), C, n);
    end = high_resolution_clock::now();
    elapsed = duration_cast<duration<double, std::milli>>(end - start);
    std::cout << elapsed.count() << std::endl;
    std::cout << C[n * n - 1] << std::endl;

    start = high_resolution_clock::now();
    mmul2(A.data(), B.data(), C, n);
    end = high_resolution_clock::now();
    elapsed = duration_cast<duration<double, std::milli>>(end - start);
    std::cout << elapsed.count() << std::endl;
    std::cout << C[n * n - 1] << std::endl;

    start = high_resolution_clock::now();
    mmul3(A.data(), B.data(), C, n);
    end = high_resolution_clock::now();
    elapsed = duration_cast<duration<double, std::milli>>(end - start);
    std::cout << elapsed.count() << std::endl;
    std::cout << C[n * n - 1] << std::endl;

    start = high_resolution_clock::now();
    mmul4(A, B, C, n);
    end = high_resolution_clock::now();
    elapsed = duration_cast<duration<double, std::milli>>(end - start);
    std::cout << elapsed.count() << std::endl;
    std::cout << C[n * n - 1] << std::endl;

    delete[] C;
    return 0;
}
