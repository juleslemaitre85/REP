#include <stdio.h>
#include <stdlib.h>

int main() {
    int repetitions = 10000;
    int success = 0;

    srand(42);

    for (int i = 0; i < repetitions; i++) {

        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        double z = (double)rand() / RAND_MAX;

        double left = (x * y) * z;
        double right = x * (y * z);

        if (left == right) {
            success++;
        }
    }

    double percentage = 100.0 * success / repetitions;

    printf("Type: double\n");
    printf("Repetitions: %d\n", repetitions);
    printf("Percentage: %.2f\n", percentage);

    return 0;
}