//
// Created by lemaitre on 09/11/2026.
//
#include <stdio.h>
#include <math.h>

#define ANNEES 50
#define FICHIER "answers_banking_llm_c.txt"

int main(void) {
    /* Capital de départ : e en double précision */
    double compte = M_E;

    /* Chaque année n : 1 euro de frais, puis multiplication par n */
    for (int n = 1; n <= ANNEES; n++) {
        compte = (compte - 1.0) * n;
    }

    /* Frais de 1 euro pour récupérer l'argent */
    compte = compte - 1.0;

    /* Mode "a" : ajoute à la suite sans écraser les résultats précédents */
    FILE *f = fopen(FICHIER, "a");
    if (f == NULL) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }

    fprintf(f, "Au bout de %d années, il y a %f sur le compte\n", ANNEES, compte);

    fclose(f);
    return 0;
}
