#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../include/pascal_poly.h"

unsigned long long* generate_pascal_coefficients(int n) {
    if (n < 0) return NULL;

    unsigned long long *row = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (!row) {
        fprintf(stderr, "Error: No se pudo asignar memoria.\n");
        exit(EXIT_FAILURE);
    }

    row[0] = 1;
    for (int i = 1; i <= n; i++) {
        row[i] = 1;
        for (int j = i - 1; j > 0; j--) {
            row[j] = row[j] + row[j - 1];
        }
    }

    return row;
}

void print_polynomial(int n, const unsigned long long *coeffs) {
    printf("f(x) = (x + 1)^%d = ", n);
    for (int i = 0; i <= n; i++) {
        int power = n - i;
        unsigned long long coeff = coeffs[i];

        if (i > 0) printf(" + ");

        if (power == 0) {
            printf("%llu", coeff);
        } else if (power == 1) {
            if (coeff == 1) printf("x");
            else printf("%llux", coeff);
        } else {
            if (coeff == 1) printf("x^%d", power);
            else printf("%llux^%d", coeff, power);
        }
    }
    printf("\n");
}

double evaluate_polynomial_step_by_step(int n, const unsigned long long *coeffs, double x) {
    printf("\n--- Evaluacion paso a paso para x = %.2f ---\n", x);
    double total_sum = 0.0;

    for (int i = 0; i <= n; i++) {
        int power = n - i;
        unsigned long long coeff = coeffs[i];
        double term_value = coeff * pow(x, power);
        total_sum += term_value;

        printf("Termino %d: %llu * (%.2f)^%d = %llu * %.4f = %.4f\n",
               i + 1, coeff, x, power, coeff, pow(x, power), term_value);
    }

    double direct_val = pow(x + 1.0, n);
    printf("----------------------------------------\n");
    printf("Suma por polinomio  : %.4f\n", total_sum);
    printf("Verificación (x+1)^n: %.4f\n", direct_val);

    return total_sum;
}

void run_benchmark_c(int n, int repetitions, const char *filename) {
    printf("\n=== BENCHMARK C (n = %d, %d repeticiones) ===\n", n, repetitions);
    
    clock_t start = clock();
    for (int r = 0; r < repetitions; r++) {
        unsigned long long *coeffs = generate_pascal_coefficients(n);
        free(coeffs);
    }
    clock_t end = clock();

    double total_seconds = ((double)(end - start)) / CLOCKS_PER_SEC;
    double avg_seconds = total_seconds / repetitions;
    double avg_ms = avg_seconds * 1000.0;

    printf("Tiempo total (%d ejecuciones): %.6f segundos\n", repetitions, total_seconds);
    printf("Tiempo promedio por ejecucion: %.8f segundos (%.6f ms)\n", avg_seconds, avg_ms);

    // Guardar resultados en archivo de texto
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: No se pudo crear el archivo %s\n", filename);
        return;
    }

    fprintf(file, "===================================================\n");
    fprintf(file, "  RESULTADOS DE EJECUCION Y BENCHMARK - LENGUAJE C\n");
    fprintf(file, "===================================================\n");
    fprintf(file, "Parametro n evaluado: %d\n", n);
    fprintf(file, "Repeticiones de prueba: %d\n", repetitions);
    fprintf(file, "Tiempo total: %.6f segundos\n", total_seconds);
    fprintf(file, "Tiempo promedio: %.8f segundos (%.6f ms)\n", avg_seconds, avg_ms);
    fprintf(file, "Estado: Ejecucion exitosa con memoria dinamica.\n");
    
    fclose(file);
    printf("Resultados guardados exitosamente en '%s'\n", filename);
}