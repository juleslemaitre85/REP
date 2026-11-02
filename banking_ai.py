import math
from decimal import Decimal, getcontext

ANNEES = 50


def banque_float(annees):
    """Calcul en flottants 64 bits (double précision IEEE 754)."""
    compte = math.e                      # e ≈ 2.718281828459045 (arrondi)
    for n in range(1, annees + 1):
        compte = (compte - 1) * n        # frais de 1 €, puis multiplication par n
    compte -= 1                          # frais de 1 € pour récupérer l'argent
    return compte


def banque_precise(annees, precision=200):
    """Même calcul avec 200 chiffres significatifs, pour comparaison."""
    getcontext().prec = precision
    compte = Decimal(1).exp()            # e avec 200 chiffres
    for n in range(1, annees + 1):
        compte = (compte - 1) * n
    compte -= 1
    return compte


# Reproductibilité : on refait le calcul plusieurs fois
resultats = [banque_float(ANNEES) for _ in range(5)]
reproductible = all(r == resultats[0] for r in resultats)

resultat = resultats[0]
resultat_precis = banque_precise(ANNEES)

print(f"Résultat en float      : {resultat:.6f}")
print(f"Résultat haute précision: {resultat_precis:.6f}")
print(f"Reproductible (5 exécutions identiques) : {reproductible}")

# Mode "a" = append : les résultats précédents ne sont pas écrasés
with open("answers_banking_llm.txt", "a") as f:
    f.write(f"Au bout de {ANNEES} années, il y a {resultat:.6f} sur le compte\n")
