import random

NB_TESTS = 1000000

compteur_vrai = 0
compteur_faux = 0

for _ in range(NB_TESTS):
    x = random.random()
    y = random.random()
    z = random.random()

    if (x + y) + z == x + (y + z):
        compteur_vrai += 1
    else:
        compteur_faux += 1

pourcentage = compteur_vrai / NB_TESTS * 100

# Mode "a" = append : les résultats précédents ne sont pas écrasés
with open("answers_associativity_llm.txt", "a") as f:
    f.write(f"compteur_faux: {compteur_faux}\n")
    f.write(f"compteur_vrai: {compteur_vrai}\n")
    f.write(f"pourcentage de vrai: {pourcentage:.6f}\n")
