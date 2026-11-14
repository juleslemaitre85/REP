from pathlib import Path
from jinja2 import Template
import subprocess

template_path = Path("templates/property.c.jinja")

template = Template(template_path.read_text())

properties = {
    "associativity": (
        "(x + y) + z",
        "x + (y + z)"
    ),

    "multiplication": (
        "(x * y) * z",
        "x * (y * z)"
    ),

    "distributivity": (
        "x * (y + z)",
        "x * y + x * z"
    )
}

types = ["float", "double"]

repetitions = 10000

Path("generated").mkdir(exist_ok=True)

for property_name, expressions in properties.items():

    lhs, rhs = expressions

    for number_type in types:

        code = template.render(
            repetitions=repetitions,
            type=number_type,
            lhs=lhs,
            rhs=rhs
        )

        filename = f"generated/{property_name}_{number_type}.c"

        Path(filename).write_text(code)

        executable = filename[:-2]

        subprocess.run(
            ["gcc", filename, "-o", executable],
            check=True
        )

        result = subprocess.run(
            [f"./{executable}"],
            capture_output=True,
            text=True,
            check=True
        )

        print(property_name, number_type)
        print(result.stdout)
