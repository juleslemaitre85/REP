#!/bin/sh
echo "debut de la compilation"

gcc egal.c -o egal -lm
gcc banking.c -o banking -lm

echo "debut de l'execution"
./egal
./banking
