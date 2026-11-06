from pascal_poly import (
    generate_pascal_coefficients,
    format_polynomial,
    evaluate_polynomial_step_by_step,
    run_benchmark_python
)

def main():
    print("===================================================")
    print("  UNEG - LENGUAJES Y COMPILADORES (2026-II)")
    print("  Prueba Diagnóstica: Ejercicio 2 (Python)")
    print("===================================================\n")

    n = 5
    x = 2.0

    coeffs = generate_pascal_coefficients(n)
    print(format_polynomial(n, coeffs))
    evaluate_polynomial_step_by_step(n, coeffs, x)

    # Ejecuta el benchmark y genera automáticamente el archivo resultados.txt
    run_benchmark_python(n=100, repetitions=10000, filename="resultados.txt")

if __name__ == "__main__":
    main()