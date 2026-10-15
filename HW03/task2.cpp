#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>

#include <omp.h>

#include "convolution.h"

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: ./task2 n t" << std::endl;
        return 1;
    }
    std::size_t n = std::strtoull(argv[1], nullptr, 10);
    int t = std::atoi(argv[2]);
    const std::size_t m = 3;

    std::random_device entropy_source;
    std::mt19937 generator(entropy_source());

    // n x n image, values in [-10, 10]
    float *image = new float[n * n];
    std::uniform_real_distribution<float> image_dist(-10.0f, 10.0f);
    for (std::size_t i = 0; i < n * n; i++) {
        image[i] = image_dist(generator);
    }

    // 3 x 3 mask, values in [-1, 1]
    float *mask = new float[m * m];
    std::uniform_real_distribution<float> mask_dist(-1.0f, 1.0f);
    for (std::size_t i = 0; i < m * m; i++) {
        mask[i] = mask_dist(generator);
    }

    float *output = new float[n * n];

    omp_set_num_threads(t);

    high_resolution_clock::time_point start = high_resolution_clock::now();
    convolve(image, output, n, mask, m);
    high_resolution_clock::time_point end = high_resolution_clock::now();
    duration<double, std::milli> elapsed = duration_cast<duration<double, std::milli>>(end - start);

    std::cout << output[0] << std::endl;
    std::cout << output[n * n - 1] << std::endl;
    std::cout << elapsed.count() << std::endl;

    delete[] image;
    delete[] mask;
    delete[] output;
    return 0;
}
