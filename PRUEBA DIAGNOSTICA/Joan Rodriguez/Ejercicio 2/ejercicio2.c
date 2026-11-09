#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

// genera la fila n del triangulo de pascal con memoria dinamica
double* generar_pascal(int n) {
    // reservar fila inicial (n = 0)
    double *fila_ant = (double*)malloc(1 * sizeof(double));
    if (fila_ant == NULL) return NULL;
    fila_ant[0] = 1.0;

    for (int i = 1; i <= n; i++) {
        // reservar memoria para la fila actual
        double *fila_act = (double*)malloc((i + 1) * sizeof(double));
        if (fila_act == NULL) {
            free(fila_ant);
            return NULL;
        }

        fila_act[0] = 1.0;
        fila_act[i] = 1.0;

        for (int j = 1; j < i; j++) {
            fila_act[j] = fila_ant[j - 1] + fila_ant[j];
        }

        // liberar fila anterior y avanzar
        free(fila_ant);
        fila_ant = fila_act;
    }

    return fila_ant;
}

// muestra los coeficientes y el polinomio (x+1)^n
void mostrar_polinomio(double *coefs, int n) {
    printf("coeficientes (n=%d): ", n);
    for (int i = 0; i <= n; i++) {
        printf("%.0f ", coefs[i]);
    }
    printf("\n(x+1)^%d = ", n);

    if (n == 0) {
        printf("1\n");
        return;
    }

    for (int i = 0; i <= n; i++) {
        int exp = n - i;
        double c = coefs[i];

        if (i > 0) printf(" + ");

        if (exp == 0) {
            printf("%.0f", c);
        } else if (exp == 1) {
            if (c > 1.0) printf("%.0fx", c);
            else printf("x");
        } else {
            if (c > 1.0) printf("%.0fx^%d", c, exp);
            else printf("x^%d", exp);
        }
    }
    printf("\n");
}

// evalua f(x) = (x+1)^n mostrando cada paso
void evaluar_paso_a_paso(double *coefs, int n, double x) {
    printf("\nevaluando f(%.0f) = (%.0f+1)^%d por pasos:\n", x, x, n);

    // memoria dinamica para guardar terminos evaluados
    double *parciales = (double*)malloc((n + 1) * sizeof(double));
    if (parciales == NULL) return;

    double suma_total = 0.0;

    for (int i = 0; i <= n; i++) {
        int exp = n - i;
        double pot = pow(x, exp);
        parciales[i] = coefs[i] * pot;
        suma_total += parciales[i];
        printf("  paso %d: coef %.0f * (%.0f^%d = %.0f) = %.0f\n",
               i + 1, coefs[i], x, exp, pot, parciales[i]);
    }

    printf("\nsuma de terminos: f(%.0f) = ", x);
    for (int i = 0; i <= n; i++) {
        if (i > 0) printf(" + ");
        printf("%.0f", parciales[i]);
    }
    printf("\nresultado final: f(%.0f) = %.0f\n", x, suma_total);

    free(parciales);
}

int main() {
    int n_prueba = 5;
    double x_prueba = 2.0;

    printf("--- prueba para n = %d, x = %.0f ---\n", n_prueba, x_prueba);
    double *coefs = generar_pascal(n_prueba);
    if (coefs != NULL) {
        mostrar_polinomio(coefs, n_prueba);
        evaluar_paso_a_paso(coefs, n_prueba, x_prueba);
        free(coefs);
    }

    // medicion de alta precision para n = 100
    printf("\n--- medicion de rendimiento para n = 100 ---\n");
    LARGE_INTEGER frecuencia, inicio, fin;
    QueryPerformanceFrequency(&frecuencia);
    QueryPerformanceCounter(&inicio);

    double *coefs_100 = generar_pascal(100);

    QueryPerformanceCounter(&fin);

    double tiempo_seg = (double)(fin.QuadPart - inicio.QuadPart) / frecuencia.QuadPart;
    double tiempo_us = tiempo_seg * 1e6;

    if (coefs_100 != NULL) {
        printf("cantidad de coeficientes generados: 101\n");
        printf("coeficiente central C(100,50): %.0f\n", coefs_100[50]);
        printf("tiempo en generar n=100 (c): %.8f segundos (%.2f microsegundos)\n", tiempo_seg, tiempo_us);
        free(coefs_100);
    }

    return 0;
}