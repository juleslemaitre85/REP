#!/bin/sh

set -e

echo "===== COMPILATION ====="

gcc -std=c90 -Wall -Wextra associativity.c -o associativity -lm
gcc -std=c90 -Wall -Wextra banking.c -o banking -lm
gcc -std=c90 -Wall -Wextra distributivity.c -o distributivity -lm

echo "===== EXECUTION ====="

./associativity
./banking
./distributivity

echo "===== FIN ====="
