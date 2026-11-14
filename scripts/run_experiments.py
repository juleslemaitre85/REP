import csv
import json
import subprocess
from pathlib import Path
from itertools import product
from jinja2 import Template

template = Template(
    Path("templates/property.c.jinja").read_text()
)

properties = {
    "AddAssociativity": (
        "(x + y) + z",
        "x + (y + z)"
    ),
    "MulAssociativity": (
        "(x * y) * z",
        "x * (y * z)"
    ),
    "Distributivity": (
        "x * (y + z)",
        "x * y + x * z"
    )
}

types = {
    "Float": "float",
    "Double": "double"
}

repetitions = {
    "R100": 100,
    "R1000": 1000,
    "R10000": 10000
}

Path("generated").mkdir(exist_ok=True)
Path("results").mkdir(exist_ok=True)

with open("configs/sample.csv", newline="") as file:
    configurations = list(csv.DictReader(file))

with open("results/results.csv", "w", newline="") as file:

    columns = [
        "config_id",
        "property",
        "type",
        "repetitions",
        "seed",
        "run",
        "percentage"
    ]

    writer = csv.DictWriter(file, fieldnames=columns)
    writer.writeheader()

    for config in configurations:

        prop = config["Property"]
        number_type = config["NumericType"]
        rep = config["Repetitions"]

        if prop not in properties:
            continue

        if number_type not in types:
            continue

        if rep not in repetitions:
            continue

        lhs, rhs = properties[prop]
        count = repetitions[rep]

        for seed in [1, 42, 123]:

            code = template.render(
                repetitions=count,
                type=types[number_type],
                lhs=lhs,
                rhs=rhs,
                seed=seed
            )

            source = Path("generated/experiment.c")
            executable = Path("generated/experiment")

            source.write_text(code)

            subprocess.run(
                ["gcc", str(source), "-o", str(executable)],
                check=True
            )

            for run in range(1, 6):

                result = subprocess.run(
                    [str(executable)],
                    capture_output=True,
                    text=True,
                    check=True
                )

                data = json.loads(result.stdout)

                writer.writerow({
                    "config_id": config["config_id"],
                    "property": prop,
                    "type": number_type,
                    "repetitions": count,
                    "seed": seed,
                    "run": run,
                    "percentage": data["percentage"]
                })

print("Experiments completed!")
