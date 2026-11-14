import argparse
import random
import secrets

FICHIER = "answers_associativity_llm.txt"
NB_TESTS_DEFAULT = 1_000_000


def main():
    parser = argparse.ArgumentParser( )

    parser.add_argument(
        "--repetitions",
        type=int,
        default=NB_TESTS_DEFAULT,
        help=f"Nb de tests à effectuer (défaut : {NB_TESTS_DEFAULT})."
    )

    parser.add_argument(
        "--seed",
        type=int,
        default=None,
        help="Graine aléatoire pour rendre l'expérience reproductible."
    )

    args = parser.parse_args()

    if args.repetitions <= 0:
        parser.error("Le nb de répétitions doit être strictement positif.")

    seed = args.seed if args.seed is not None else secrets.randbits(32)
    random.seed(seed)

    compteur_vrai = 0
    compteur_faux = 0

    for _ in range(args.repetitions):
        x = random.random()
        y = random.random()
        z = random.random()

        if (x + y) + z == x + (y + z):
            compteur_vrai += 1
        else:
            compteur_faux += 1

    pourcentage = compteur_vrai / args.repetitions * 100

    # Affichage des résultats
    print(f"Graine utilisée : {seed}")
    print(f"Nombre de tests : {args.repetitions}")
    print(f"compteur_faux : {compteur_faux}")
    print(f"compteur_vrai : {compteur_vrai}")
    print(f"pourcentage de vrai : {pourcentage:.6f}%")

    # Enregistrement des résultats (mode append)
    with open(FICHIER, "a") as f:
        f.write(f"seed: {seed}\n")
        f.write(f"repetitions: {args.repetitions}\n")
        f.write(f"compteur_faux: {compteur_faux}\n")
        f.write(f"compteur_vrai: {compteur_vrai}\n")
        f.write(f"pourcentage de vrai: {pourcentage:.6f}\n")
        f.write("\n")


if __name__ == "__main__":
    main()