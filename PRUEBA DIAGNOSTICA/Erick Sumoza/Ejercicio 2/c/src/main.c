#include <stdio.h>
#include <stdlib.h>
#include "../include/pascal_poly.h"

int main(void) {
    printf("===================================================\n");
    printf("  UNEG - LENGUAJES Y COMPILADORES (2026-II)\n");
    printf("  Prueba Diagnostica: Ejercicio 2 (Lenguaje C)\n");
    printf("===================================================\n\n");

    int n = 5;
    double x = 2.0;

    unsigned long long *coeffs = generate_pascal_coefficients(n);
    print_polynomial(n, coeffs);
    evaluate_polynomial_step_by_step(n, coeffs, x);
    free(coeffs);

    // Ejecuta el benchmark y genera automáticamente el archivo resultados.txt
    run_benchmark_c(100, 10000, "resultados.txt");

    return 0;
}