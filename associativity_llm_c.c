//
// Created by lemaitre on 09/11/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_TESTS 10000
#define FICHIER "answers_associativity_llm_c.txt"

/* Tire un double aléatoire dans [0, 1) */
static double aleatoire(void) {
    return (double)rand() / ((double)RAND_MAX + 1.0);
}

int main(void) {
    int compteur_vrai = 0;
    int compteur_faux = 0;

    /* Graine différente à chaque exécution */
    srand((unsigned int)time(NULL) ^ (unsigned int)clock());

    for (int i = 0; i < NB_TESTS; i++) {
        double x = aleatoire();
        double y = aleatoire();
        double z = aleatoire();

        double gauche = (x + y) + z;
        double droite = x + (y + z);

        if (gauche == droite) {
            compteur_vrai++;
        } else {
            compteur_faux++;
        }
    }

    double pourcentage = 100.0 * compteur_vrai / NB_TESTS;

    /* Mode "a" : ajoute à la suite sans écraser les résultats précédents */
    FILE *f = fopen(FICHIER, "a");
    if (f == NULL) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }

    fprintf(f, "compteur_faux: %d\n", compteur_faux);
    fprintf(f, "compteur_vrai: %d\n", compteur_vrai);
    fprintf(f, "pourcentage de vrai: %f\n", pourcentage);

    fclose(f);
    return 0;
}
