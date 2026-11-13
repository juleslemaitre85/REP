#include <stdio.h>
#include <stdlib.h>

// Fonction pour générer un double entre min et max
double rand_double(double min, double max) {
    double scale = (double)rand() / (double)RAND_MAX; // Entre 0.0 et 1.0
    return min + scale * (max - min);                 // Mise à l'échelle
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

int main() {
    fonction(100);
    fonction(1000);
    fonction(10000);
    fonction(1000000);
    return 0;
}
