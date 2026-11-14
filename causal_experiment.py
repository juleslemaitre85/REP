"""Expérience causale (TP3, partie 8) : on n'intervient que sur le type de nombre.

Même graine => mêmes triplets tirés (en float64), puis convertis dans le type testé.
Le seul facteur qui change entre deux lignes d'une même graine est `number_type`.

Usage : python causal_experiment.py --repetitions 100000 --seeds 30 -o results/causal.csv
Sortie : CSV (seed, number_type, repetitions, percentage)
"""
import argparse
import csv
from fractions import Fraction
from pathlib import Path

import numpy as np

parser = argparse.ArgumentParser()
parser.add_argument("--repetitions", type=int, default=100_000)
parser.add_argument("--exact-repetitions", type=int, default=2_000,
                    help="répétitions pour les fractions (lent)")
parser.add_argument("--seeds", type=int, default=30)
parser.add_argument("-o", "--output", default="results/causal.csv")
args = parser.parse_args()


def pct_float(x, y, z):
    return 100 * float(np.mean((x + y) + z == x + (y + z)))


rows = []
for seed in range(args.seeds):
    rng = np.random.default_rng(seed)
    x, y, z = (rng.random(args.repetitions) for _ in range(3))      # float64 dans [0, 1)
    rows.append((seed, "float64", args.repetitions, pct_float(x, y, z)))
    rows.append((seed, "float32", args.repetitions,
                 pct_float(x.astype(np.float32), y.astype(np.float32), z.astype(np.float32))))

    # entiers tirés avec la même graine : arithmétique exacte (int64 sans débordement ici)
    rng = np.random.default_rng(seed)
    xi, yi, zi = (rng.integers(0, 2**20, args.repetitions, dtype=np.int64) for _ in range(3))
    rows.append((seed, "int", args.repetitions, pct_float(xi, yi, zi)))

    # fractions exactes construites à partir des MÊMES flottants (aucun arrondi dans l'addition)
    n = args.exact_repetitions
    holds = sum(
        (Fraction(float(a)) + Fraction(float(b))) + Fraction(float(c))
        == Fraction(float(a)) + (Fraction(float(b)) + Fraction(float(c)))
        for a, b, c in zip(x[:n], y[:n], z[:n])
    )
    rows.append((seed, "fraction", n, 100 * holds / n))

out = Path(args.output)
out.parent.mkdir(parents=True, exist_ok=True)
with out.open("w", newline="") as f:
    w = csv.writer(f)
    w.writerow(["seed", "number_type", "repetitions", "percentage"])
    w.writerows(rows)
print(f"{len(rows)} lignes écrites dans {out}")
