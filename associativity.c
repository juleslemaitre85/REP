#include <stdio.h>
#include <stdlib.h>

/* Fonction pour générer un double entre min et max */
double rand_double(double min, double max) {
    double scale = (double)rand() / (double)RAND_MAX; /* Entre 0.0 et 1.0 */
    return min + scale * (max - min);                 /* Mise à l'échelle*/
}

void fonction(int number) {
    int n = number;
    int compteur_vrai = 0;
    int compteur_faux = 0;
    double x, y, z;
    int i;
    for ( i = 0; i < n; i++) {
        x = rand_double(-100000, 100000);
        y = rand_double(-100000, 100000);
        z = rand_double(-100000, 100000);
        if ((x+y)+z==x+(y+z)){
            compteur_vrai += 1;
    } else {
            compteur_faux += 1;
        }
    }
    FILE *file = fopen("answers_associativity.txt","a");
    double pourcentage;
    pourcentage = (double)compteur_vrai/n*100;
    fprintf(file,"compteur_faux: %d \n", compteur_faux);
    fprintf(file,"compteur_vrai: %d \n", compteur_vrai);
    fprintf(file,"pourcentage de vrai: %lf \n", pourcentage );
    fclose(file);

}
double check_associativity(int repetitions) {
    int success = 0;

    for (int i = 0; i < repetitions; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        double z = (double)rand() / RAND_MAX;

        if ((x + y) + z == x + (y + z)) {
            success++;
        }
    }

    return 100.0 * success / repetitions;
}

int main() {
    int values[] = {100, 1000, 10000, 100000, 1000000};

    for (int i = 0; i < 5; i++) {
        int repetitions = values[i];

        double result = check_associativity(repetitions);

        printf("Repetitions: %d | Result: %.2f%%\n",
               repetitions, result);
    }

    return 0;
}
