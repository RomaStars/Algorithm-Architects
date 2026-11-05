/**
 * Universidad Nacional Experimental de Guayana (UNEG)
 * Coordinación de Ingeniería en Informática - Lenguajes y Compiladores
 * Periodo lectivo: 2026-II - Prueba Diagnóstica
 * Estudiante: Alexander Fernández
 * Ejercicio 2: Generación de Polinomio (x+1)^n mediante Triángulo de Pascal y Memoria Dinámica
 * Lenguaje: C (Estándar ANSI C / C99, sin librerías externas)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#if defined(_WIN32)
#include <windows.h>
#endif

/* Obtiene el directorio donde reside el ejecutable para guardar los resultados siempre en su carpeta */
void obtener_directorio_base(const char *argv0, char *dir, size_t dir_size) {
#if defined(_WIN32)
    char exe_path[MAX_PATH];
    if (GetModuleFileNameA(NULL, exe_path, MAX_PATH)) {
        char *sep = strrchr(exe_path, '\\');
        if (!sep) sep = strrchr(exe_path, '/');
        if (sep) {
            *sep = '\0';
            strncpy(dir, exe_path, dir_size);
            return;
        }
    }
#endif
    if (argv0) {
        strncpy(dir, argv0, dir_size);
        char *sep1 = strrchr(dir, '\\');
        char *sep2 = strrchr(dir, '/');
        char *sep = (sep2 && (!sep1 || sep2 > sep1)) ? sep2 : sep1;
        if (sep) {
            *sep = '\0';
            return;
        }
    }
    dir[0] = '.';
    dir[1] = '\0';
}

/* Temporizador de alta precisión (resolución de microsegundos) */
double obtener_tiempo_segundos(void) {
#if defined(_WIN32)
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart / (double)freq.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
#endif
}

/* Función para sumar dos números enteros arbitrariamente grandes representados como cadenas (BigInt) */
char* sumar_bigint(const char *a, const char *b) {
    int len_a = (int)strlen(a);
    int len_b = (int)strlen(b);
    int max_len = len_a > len_b ? len_a : len_b;
    
    /* Memoria dinámica para el resultado (máx dígitos + acarreo + '\0') */
    char *res = (char *)malloc(max_len + 2);
    if (!res) return NULL;

    int i = len_a - 1;
    int j = len_b - 1;
    int k = 0;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += (a[i--] - '0');
        if (j >= 0) sum += (b[j--] - '0');
        carry = sum / 10;
        res[k++] = (sum % 10) + '0';
    }
    res[k] = '\0';

    /* Invertir la cadena para obtener el orden correcto de dígitos */
    for (int l = 0, r = k - 1; l < r; l++, r--) {
        char temp = res[l];
        res[l] = res[r];
        res[r] = temp;
    }
    return res;
}

/* Duplica una cadena en memoria dinámica (equivalente portátil a strdup) */
char* duplicar_cadena(const char *s) {
    size_t len = strlen(s);
    char *d = (char *)malloc(len + 1);
    if (d) strcpy(d, s);
    return d;
}

/**
 * Genera la fila n del triángulo de Pascal utilizando memoria dinámica.
 * Retorna un arreglo dinámico de cadenas (char**) con n+1 coeficientes BigInt.
 */
char** generar_pascal_bigint(int n) {
    if (n < 0) return NULL;

    char **fila_actual = (char **)malloc(sizeof(char *));
    fila_actual[0] = duplicar_cadena("1");

    for (int r = 1; r <= n; r++) {
        char **siguiente_fila = (char **)malloc((r + 1) * sizeof(char *));
        siguiente_fila[0] = duplicar_cadena("1");
        siguiente_fila[r] = duplicar_cadena("1");

        for (int j = 1; j < r; j++) {
            siguiente_fila[j] = sumar_bigint(fila_actual[j - 1], fila_actual[j]);
        }

        /* Liberar la fila previa de la memoria dinámica */
        for (int j = 0; j < r; j++) {
            free(fila_actual[j]);
        }
        free(fila_actual);

        fila_actual = siguiente_fila;
    }
    return fila_actual;
}

/* Libera la memoria dinámica de una fila de coeficientes */
void liberar_fila(char **fila, int n) {
    if (!fila) return;
    for (int i = 0; i <= n; i++) {
        free(fila[i]);
    }
    free(fila);
}

/* Imprime la representación algebraica de (x+1)^n */
void imprimir_polinomio(char **coefs, int n) {
    if (n == 0) {
        printf("1\n");
        return;
    }
    for (int i = 0; i <= n; i++) {
        int pot = n - i;
        if (i > 0) printf(" + ");

        int es_uno = (strcmp(coefs[i], "1") == 0);
        if (pot == 0) {
            printf("%s", coefs[i]);
        } else if (pot == 1) {
            if (es_uno) printf("x");
            else printf("%sx", coefs[i]);
        } else {
            if (es_uno) printf("x^%d", pot);
            else printf("%sx^%d", coefs[i], pot);
        }
    }
    printf("\n");
}

/* Evaluación paso a paso para valores de x y n representativos */
void evaluar_paso_a_paso(int n, long long x) {
    printf("\n======================================================================\n");
    printf("   EVALUACION PASO A PASO: f(%lld) para n = %d\n", x, n);
    printf("======================================================================\n");

    /* Generación con memoria dinámica */
    char **coefs = generar_pascal_bigint(n);

    printf("Polinomio generado: P(x) = ");
    imprimir_polinomio(coefs, n);

    printf("\n[PASO 1] Planteamiento de la formula con coeficientes:\n  f(x) = ");
    for (int i = 0; i <= n; i++) {
        int pot = n - i;
        if (i > 0) printf(" + ");
        if (pot > 1) printf("(%s)*x^%d", coefs[i], pot);
        else if (pot == 1) printf("(%s)*x", coefs[i]);
        else printf("(%s)", coefs[i]);
    }
    printf("\n");

    printf("\n[PASO 2] Sustitucion del valor dado x = %lld:\n  f(%lld) = ", x, x);
    for (int i = 0; i <= n; i++) {
        int pot = n - i;
        if (i > 0) printf(" + ");
        if (pot > 1) printf("(%s)*(%lld)^%d", coefs[i], x, pot);
        else if (pot == 1) printf("(%s)*(%lld)", coefs[i], x);
        else printf("(%s)*1", coefs[i]);
    }
    printf("\n");

    printf("\n[PASO 3] Calculo individual de potencias:\n");
    long long *potencias = (long long *)malloc((n + 1) * sizeof(long long));
    for (int i = 0; i <= n; i++) {
        int pot = n - i;
        long long val = 1;
        for (int p = 0; p < pot; p++) val *= x;
        potencias[i] = val;
        printf("  (%lld)^%d = %lld\n", x, pot, val);
    }

    printf("\n[PASO 4] Multiplicacion de coeficientes por su potencia correspondiente:\n");
    long long *terminos = (long long *)malloc((n + 1) * sizeof(long long));
    long long suma_total = 0;
    for (int i = 0; i <= n; i++) {
        int pot = n - i;
        long long c = atoll(coefs[i]);
        terminos[i] = c * potencias[i];
        suma_total += terminos[i];
        printf("  Termino %d (x^%d): %lld * %lld = %lld\n", i + 1, pot, c, potencias[i], terminos[i]);
    }

    printf("\n[PASO 5] Suma algebraica acumulada:\n  f(%lld) = ", x);
    for (int i = 0; i <= n; i++) {
        if (i > 0) printf(" + ");
        printf("%lld", terminos[i]);
    }
    printf("\n  f(%lld) = %lld\n", x, suma_total);

    /* Verificación con (x + 1)^n */
    long long directo = 1;
    for (int p = 0; p < n; p++) directo *= (x + 1);

    printf("\n[PASO 6] Verificacion directa: f(%lld) = (%lld + 1)^%d = (%lld)^%d = %lld\n",
           x, x, n, x + 1, n, directo);

    if (suma_total == directo) {
        printf("  [VERIFICACION EXITOSA]: %lld == %lld\n", suma_total, directo);
    } else {
        printf("  [ERROR]: Discrepancia detectada\n");
    }

    /* Liberación de memoria dinámica */
    free(potencias);
    free(terminos);
    liberar_fila(coefs, n);
}

void demostrar_guia() {
    printf("======================================================================\n");
    printf("   UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n");
    printf("   LENGUAJES Y COMPILADORES - PRUEBA DIAGNOSTICA\n");
    printf("   EJERCICIO 2: POLINOMIO (x+1)^n Y TRIANGULO DE PASCAL (LENGUAJE C)\n");
    printf("======================================================================\n\n");
    printf("[+] GENERACION DE POLINOMIOS DE LA GUIA (n = 0 hasta 7):\n");

    for (int n = 0; n <= 7; n++) {
        char **c = generar_pascal_bigint(n);
        printf(" (n=%d): ", n);
        for (int j = 0; j <= n; j++) {
            printf("%s ", c[j]);
        }
        printf(" -> (x+1)^%d = ", n);
        imprimir_polinomio(c, n);
        liberar_fila(c, n);
    }
}

void benchmark_c_n100(const char *dir_base) {
    printf("\n======================================================================\n");
    printf("[+] MEDICION DE RENDIMIENTO PARA n = 100 EN C (MEMORIA DINAMICA):\n");

    int iteraciones = 200;
    double inicio = obtener_tiempo_segundos();
    char **c100 = NULL;
    for (int i = 0; i < iteraciones; i++) {
        if (c100) liberar_fila(c100, 100);
        c100 = generar_pascal_bigint(100);
    }
    double fin = obtener_tiempo_segundos();

    double tiempo_total_ms = (fin - inicio) * 1000.0;
    double tiempo_promedio_ms = tiempo_total_ms / iteraciones;

    printf(" - Coeficientes generados para n=100 : 101 coeficientes\n");
    printf(" - Coeficiente central C(100, 50)    : %s\n", c100[50]);
    printf(" - Tiempo promedio de ejecucion en C : %.4f ms\n", tiempo_promedio_ms);

    /* Guardar/Sobreescribir archivo de resultados en la carpeta propia del ejercicio */
    char ruta_reporte[512];
    snprintf(ruta_reporte, sizeof(ruta_reporte), "%s/resultado_tiempos_c.txt", dir_base);
    FILE *f = fopen(ruta_reporte, "w"); /* Modo "w" asegura sobreescritura */
    if (f) {
        fprintf(f, "UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n");
        fprintf(f, "PRUEBA DIAGNOSTICA - LENGUAJES Y COMPILADORES\n");
        fprintf(f, "ESTUDIANTE: Alexander Fernandez\n");
        fprintf(f, "EJERCICIO 2: POLINOMIO (x+1)^n CON TRIANGULO DE PASCAL (C)\n");
        fprintf(f, "======================================================================\n\n");
        fprintf(f, "1. MEDICION DE RENDIMIENTO PARA n = 100 (MEMORIA DINAMICA CON BIGINT):\n");
        fprintf(f, "   - Tiempo promedio en C : %.4f ms (medido sobre %d iteraciones)\n", tiempo_promedio_ms, iteraciones);
        fprintf(f, "   - Coeficiente central C(100, 50): %s\n", c100[50]);
        fprintf(f, "   - Total de coeficientes generados: 101\n\n");
        fprintf(f, "2. POLINOMIO GENERADO PARA n = 4:\n");
        fprintf(f, "   P(x) = x^4 + 4x^3 + 6x^2 + 4x + 1\n\n");
        fprintf(f, "3. EVALUACION PASO A PASO PARA f(3) con n = 4:\n");
        fprintf(f, "   Resultado final = 256\n");
        fprintf(f, "   Verificacion: (3 + 1)^4 = (4)^4 = 256 [CORRECTO]\n");
        fclose(f);
        printf("[OK] Reporte guardado/sobreescrito exitosamente en: '%s'\n", ruta_reporte);
    }
    liberar_fila(c100, 100);
}

int main(int argc, char *argv[]) {
    char dir_base[512];
    obtener_directorio_base(argv[0], dir_base, sizeof(dir_base));

    if (argc == 3) {
        int n = atoi(argv[1]);
        long long x = atoll(argv[2]);
        evaluar_paso_a_paso(n, x);
    } else {
        demostrar_guia();
        evaluar_paso_a_paso(4, 3);
        benchmark_c_n100(dir_base);
    }
    return 0;
}

