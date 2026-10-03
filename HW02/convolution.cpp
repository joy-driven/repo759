#include "convolution.h"

void convolve(const float *image, float *output, std::size_t n, const float *mask, std::size_t m) {
    const long N = static_cast<long>(n);
    const long M = static_cast<long>(m);
    const long r = (M - 1) / 2;

    for (long x = 0; x < N; x++) {
        for (long y = 0; y < N; y++) {
            float sum = 0.0f;
            for (long i = 0; i < M; i++) {
                const long fx = x + i - r;
                const bool x_in = (fx >= 0 && fx < N);
                for (long j = 0; j < M; j++) {
                    const long fy = y + j - r;
                    const bool y_in = (fy >= 0 && fy < N);
                    float f;
                    if (x_in && y_in) {
                        f = image[fx * N + fy];
                    } else if (x_in || y_in) {
                        // edge (one index out of range): pad with 1
                        f = 1.0f;
                    } else {
                        // corner (both out of range): pad with 0
                        f = 0.0f;
                    }
                    sum += mask[i * M + j] * f;
                }
            }
            output[x * N + y] = sum;
        }
    }
}
