//
// Created by lemaitre on 12/10/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main() {
    int n = 50;
    double compte = exp(1.0);
    printf("compte à n=0: %lf\n",compte);
    int x, y, z;
    int i;
    for ( i = 1; i < n+1; i++) {
        compte = (compte-1)*i;
    }
    //double pourc = compteur_vrai/n*100;
    printf("Au bout de %d années, il y a %lf sur le compte\n",n,compte);
}

