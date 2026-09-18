#include <cstdio>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./task6 N" << std::endl;
        return 1;
    }
    int N = std::atoi(argv[1]);

    // 0 to N with printf
    for (int i = 0; i <= N; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", i);
    }
    printf("\n");

    // N to 0 with std::cout
    for (int i = N; i >= 0; i--) {
        std::cout << i;
        if (i > 0) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;

    return 0;
}
