#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <limits.h>

#define NB_TESTS_DEFAULT 10000
#define FICHIER "answers_associativity_llm_c.txt"

/* Tire un double aléatoire dans [0, 1) */
static double aleatoire(void) {
    return (double)rand() / ((double)RAND_MAX + 1.0);
}

int main(int argc, char *argv[]) {

    int nb_tests = NB_TESTS_DEFAULT;
    unsigned int seed = (unsigned int)(time(NULL) ^ clock());
    int seed_specifiee = 0;

    /* Lecture des arguments CLI */
    for (int i = 1; i < argc; i++) {

        if (strncmp(argv[i], "--repetitions=", 14) == 0) {

            char *end;
            errno = 0;
            long valeur = strtol(argv[i] + 14, &end, 10);

            if (errno != 0 || *end != '\0' ||
                valeur <= 0 || valeur > INT_MAX) {
                fprintf(stderr, "Nombre de repetitions invalide.\n");
                return 1;
            }

            nb_tests = (int)valeur;
        }

        else if (strncmp(argv[i], "--seed=", 7) == 0) {

            char *end;
            errno = 0;
            unsigned long valeur = strtoul(argv[i] + 7, &end, 10);

            if (errno != 0 || *end != '\0' || valeur > UINT_MAX) {
                fprintf(stderr, "Seed invalide.\n");
                return 1;
            }

            seed = (unsigned int)valeur;
            seed_specifiee = 1;
        }

        else if (strcmp(argv[i], "--help") == 0) {
            printf("Utilisation : %s [options]\n", argv[0]);
            printf("Options :\n");
            printf("  --repetitions=N   Nombre de tests (defaut : %d)\n",
                   NB_TESTS_DEFAULT);
            printf("  --seed=N          Graine aleatoire\n");
            printf("  --help            Afficher cette aide\n");
            return 0;
        }

        else {
            fprintf(stderr, "Argument inconnu : %s\n", argv[i]);
            return 1;
        }
    }

    /* Initialisation du generateur */
    srand(seed);

    int compteur_vrai = 0;
    int compteur_faux = 0;

    for (int i = 0; i < nb_tests; i++) {

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

    double pourcentage = 100.0 * compteur_vrai / nb_tests;

    /* Affichage dans le terminal */
    printf("Nombre de repetitions : %d\n", nb_tests);
    printf("Seed : %u (%s)\n", seed,
           seed_specifiee ? "specifiee" : "automatique");
    printf("Compteur vrai : %d\n", compteur_vrai);
    printf("Compteur faux : %d\n", compteur_faux);
    printf("Pourcentage de vrai : %.6f%%\n", pourcentage);

    /* Enregistrement dans le fichier */
    FILE *f = fopen(FICHIER, "a");

    if (f == NULL) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }

    fprintf(f, "repetitions: %d\n", nb_tests);
    fprintf(f, "seed: %u\n", seed);
    fprintf(f, "compteur_faux: %d\n", compteur_faux);
    fprintf(f, "compteur_vrai: %d\n", compteur_vrai);
    fprintf(f, "pourcentage de vrai: %.6f\n\n", pourcentage);

    fclose(f);

    return 0;
}