# REP — Reproducibility of Experimentations

This repository contains experiments exploring the reproducibility of computational results and the impact of different variability factors, such as programming languages, execution environments, and program configurations.

---

# Lab 1 — Initial Experiments

The experiments can be reproduced by running the following programs:

| Program | Experiment | Description |
|---|---|---|
| `egal.c` | Associativity | Checks whether `(x + y) + z = x + (y + z)`. |
| `banking.c` | Banking problem | Simulates the banking investment problem. |



---

# Lab 2 — Reproducibility with git, Docker and GitHub Actions

The results are written to the following files:

- `answers_associativity.txt`
- `answers_banking.txt`

Previous results are already stored in these files.


Two programs were generated using Claude AI:

- `banking_ai.py`
- `associativity_ai.py`

The following prompts were used.

### Associativity experiment

```text
Donne moi un programme en python qui vérifie si
(x+y)+z=x+(y+z).

A chaque fois que le programme tourne, il vérifie
10000 fois pour des x, y et z différents (aléatoires)
et écris dans le fichier answers_associativity_llm.txt
le résultat sous cette forme:

compteur_faux: 760915
compteur_vrai: 9239085
pourcentage de vrai: 92.390850

(attention le résultat doit être écrit à la suite,
sans écraser les réponse précédentes).
```

### Banking experiment

```text
Ecris un programme en python; The banking problem:
do the same.

"My banker proposed this investment to me: you give
me e ≈ 2.71828… The following year, I take 1 euro
as a fee and multiply by 1. The next year, I take
1 euro as a fee and multiply by 2. The next year,
I take 1 euro as a fee and multiply by 3. […] After
n years, I take 1 euro as a fee and multiply by n.
To retrieve my money, there is a 1 euro fee.
In 50 years, for my retirement, how much money
will I have?"

Write a program that answers this question, write
down your choices, and check whether your result
is reproducible.

Cette fois, le fichier où écrire les réponse sera
"answers_banking_llm.txt", sous la forme:

Au bout de 50 années, il y a
-4396803930182068517325088235103664583272782888960.000000
sur le compte
```

### Comparison of Results

For the associativity experiment, the AI-generated Python implementation uses random floating-point numbers between 0 and 1.

The results differ significantly:

- Original implementation: approximately **92%** correct results.
- AI-generated implementation: approximately **82%** correct results.

This difference may be explained by the choice of random values and the numerical operations performed. Floating-point arithmetic is sensitive to rounding errors, which can affect the equality comparison.


We then create a Dockerfile to help reproduce the experiment.

---

# Lab 3 — Studying Variability and Reproducibility

## 1. Identifying Variability Factors

Several factors can influence the results of an experiment:

- **Programming language:** different languages may handle numerical operations differently.
- **Number of repetitions:** changing the number of iterations can affect the results.
- **Computing environment:** the operating system and execution environment may influence the outcome.
- **Program implementation:** different implementations of the same experiment may produce different results.
- **Compilation settings:** compiler options and optimizations can affect numerical computations.

## 2. AI-Generated Programs

We compare the different results that we obtained with our code and the ai's, and observe that they are differences, that may have several causes.

The following table summarizes the main implementation differences:

| Factor | TP1 (C) | TP2 (Python) | New LLM (C) |
|---|---|---|---|
| Programming language | C | Python | C |
| Numeric type | `double` | `float` (Python double precision) | `double` |
| Number of repetitions | 10,000,000 | 10,000 | 10,000 |
| Random generator | `rand()` | `random.random()` | `rand()` |
| Compilation | GCC | Interpreter | GCC |
| Optimization | `-O0` | None | `-O2` |
| Comparison | `==` | `==` | `==` |

For the banking problem, the results obtained with the original implementation and the AI-generated implementation are identical.

---

## 3. Variability Mechanisms

Several mechanisms were implemented to investigate the impact of variability on experimental results.

### 3.1 Runtime Parameters

The number of repetitions influences the results of the associativity experiment.

For example:

| Number of repetitions | Percentage of correct results |
|---:|---:|
| 100 | 79.00% |
| 1,000 | 73.00% |
| 10,000 | 74.34% |
| 100,000 | 74.64% |
| 1,000,000 | 74.54% |

These results illustrate that changing runtime parameters can lead to different experimental outcomes.

### 3.2 Command-Line Interface (CLI)

The programs do not necessarily produce identical results, even when executed with the same parameters.

This highlights the importance of considering the implementation and execution conditions when studying reproducibility.

### 3.3 Template-Based Generation

We use a Jinja template to generate multiple program variants automatically.

This allows us to experiment with different configurations while keeping a common program structure.

### 3.4 Computing Environment

We use GitHub Actions to execute experiments under different computing environments.

In particular, we vary the Ubuntu version to investigate whether the operating system influences the results.

---

## 4. Modelling Variability Factors

We model the different variability factors using a UVL feature model.

After drawing the UVL diagram, we identified **126 valid configurations**.

These configurations describe the possible combinations of variability factors that can influence our experiments.

We can then use the Configurator tool to represent and manage the different program configurations.

---

## 5. Sampling Configurations

Our objective is to generate a random and reproducible sample of configurations.

We use `sample.py` to generate this sample.

We selected a sample size of **30 configurations** as a compromise between:

- Configuration diversity.
- Execution time.
- The number of variability factors being investigated.

Using a fixed random seed ensures that the sample can be reproduced.

---

## 6. Serializing Experimental Results

The script `run_experiments.py` executes the experiments using different configurations and stores the results in a CSV file named `results.csv`.

Each row corresponds to an experiment execution.

The columns contain information about each run, including:

- Program.
- Property being tested.
- Numeric type.
- Configuration.
- Experimental results.

This CSV file provides a structured dataset for further analysis.

---

## 7. Automated Execution with GitHub Actions

We created a GitHub Actions workflow named `variability.yml` to automate the experimental process.

The workflow executes the previous steps automatically, allowing us to test the impact of different configurations.

In particular, it investigates the variability of the computing environment by running experiments with different Ubuntu versions.

This automation helps ensure that the experiments can be executed consistently and repeatedly.

---

## 8. Analysis of Experimental Results

We analyse the experimental results using a Jupyter Notebook available in the GitHub repository.

The notebook processes the data stored in `results.csv` and provides visualizations to compare the different configurations and identify potential variability factors.

AI was used to generate the initial structure (skeleton) of the notebook.
