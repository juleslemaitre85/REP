#include <stdio.h>
#include <stdlib.h>

// Fonction pour générer un double entre min et max
double rand_double(double min, double max) {
    double scale = (double)rand() / (double)RAND_MAX; // Entre 0.0 et 1.0
    return min + scale * (max - min);                 // Mise à l'échelle
}

void main() {
    int n = 10000000;
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
    double pourcentage;
    pourcentage = (double)compteur_vrai/n*100;
    printf("compteur_faux: %d \n", compteur_faux);
    printf("compteur_vrai: %d \n", compteur_vrai);
    printf("pourcentage de vrai: %lf \n", pourcentage );
}
