#include <stdio.h>
#include <stdlib.h>

int main() {
    int repetitions = 10000;
    int success = 0;

    srand(42);

    for (int i = 0; i < repetitions; i++) {

        float x = (float)rand() / RAND_MAX;
        float y = (float)rand() / RAND_MAX;
        float z = (float)rand() / RAND_MAX;

        float left = (x * y) * z;
        float right = x * (y * z);

        if (left == right) {
            success++;
        }
    }

    double percentage = 100.0 * success / repetitions;

    printf("Type: float\n");
    printf("Repetitions: %d\n", repetitions);
    printf("Percentage: %.2f\n", percentage);

    return 0;
}