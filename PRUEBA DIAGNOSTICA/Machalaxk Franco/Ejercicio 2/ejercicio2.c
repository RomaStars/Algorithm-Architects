/* ============================================================================
 * EJERCICIO 2 - PRUEBA DIAGNÓSTICA
 * Lenguajes y Compiladores - UNEG - Periodo 2026-II
 * ----------------------------------------------------------------------------
 * Dado n >= 0 entero:
 *   a) Genera los coeficientes del polinomio (x+1)^n usando el
 *      TRIÁNGULO DE PASCAL, y muestra el polinomio resultante.
 *   b) Con esos coeficientes c_0..c_n, evalúa f(x) = sum c_i * x^i
 *      mostrando PASO A PASO cada término y la suma total.
 *
 * CORRECCIÓN PARA WINDOWS:
 *   Se utiliza 'unsigned long long' y '%llu' en lugar de 'uint64_t' y '%lu'.
 *
 * IMPLEMENTACIÓN:
 *   - En C los coeficientes crecen muchísimo, así que se implementa un 
 *     EnteroGrande dinámico en base 10^9 con malloc/realloc.
 * ==========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define BASE 1000000000u

typedef struct {
    uint32_t *digitos;
    int longitud;
    int capacidad;
} EnteroGrande;

/* ---------------------------------------------------------------------------
 * FUNCIONES DEL ENTERO GRANDE (MEMORIA DINÁMICA)
 * -------------------------------------------------------------------------*/
static void inicializar_entero_grande(EnteroGrande *num, int cap) {
    num->digitos = (uint32_t *)calloc(cap, sizeof(uint32_t));
    num->longitud = 1;
    num->capacidad = cap;
    num->digitos[0] = 0;
}

static void liberar_entero_grande(EnteroGrande *num) {
    free(num->digitos);
    num->digitos = NULL;
    num->longitud = 0;
    num->capacidad = 0;
}

static void asegurar_capacidad(EnteroGrande *num, int cap) {
    if (num->capacidad < cap) {
        if (num->capacidad == 0) num->capacidad = 4;
        while (num->capacidad < cap) num->capacidad *= 2;
        num->digitos = (uint32_t *)realloc(num->digitos, num->capacidad * sizeof(uint32_t));
    }
}

static void asignar_valor_pequeno(EnteroGrande *num, unsigned long long valor) {
    if (valor == 0) {
        asegurar_capacidad(num, 1);
        num->digitos[0] = 0;
        num->longitud = 1;
        return;
    }
    int longitud = 0;
    unsigned long long temp = valor;
    while (temp > 0) { longitud++; temp /= BASE; }

    asegurar_capacidad(num, longitud);
    num->longitud = longitud;
    for (int i = 0; i < longitud; i++) {
        num->digitos[i] = (uint32_t)(valor % BASE);
        valor /= BASE;
    }
}

static void sumar_enteros(EnteroGrande *destino, const EnteroGrande *a, const EnteroGrande *b) {
    int max_long = (a->longitud > b->longitud) ? a->longitud : b->longitud;
    asegurar_capacidad(destino, max_long + 1);

    unsigned long long acarreo = 0;
    for (int i = 0; i < max_long; i++) {
        unsigned long long suma = acarreo;
        if (i < a->longitud) suma += a->digitos[i];
        if (i < b->longitud) suma += b->digitos[i];
        destino->digitos[i] = (uint32_t)(suma % BASE);
        acarreo = suma / BASE;
    }
    destino->longitud = max_long;
    if (acarreo > 0) destino->digitos[destino->longitud++] = (uint32_t)acarreo;
}

static void multiplicar_enteros(EnteroGrande *destino, const EnteroGrande *a, const EnteroGrande *b) {
    int nueva_longitud = a->longitud + b->longitud;
    uint32_t *temporal = (uint32_t *)calloc(nueva_longitud, sizeof(uint32_t));

    for (int i = 0; i < a->longitud; i++) {
        unsigned long long acarreo = 0;
        for (int j = 0; j < b->longitud; j++) {
            unsigned long long producto = (unsigned long long)a->digitos[i] * b->digitos[j] + temporal[i + j] + acarreo;
            temporal[i + j] = (uint32_t)(producto % BASE);
            acarreo = producto / BASE;
        }
        int k = i + b->longitud;
        while (acarreo > 0) {
            unsigned long long suma = temporal[k] + acarreo;
            temporal[k] = (uint32_t)(suma % BASE);
            acarreo = suma / BASE;
            k++;
        }
    }

    int longitud = nueva_longitud;
    while (longitud > 1 && temporal[longitud - 1] == 0) longitud--;

    asegurar_capacidad(destino, longitud);
    memcpy(destino->digitos, temporal, longitud * sizeof(uint32_t));
    destino->longitud = longitud;
    free(temporal);
}

static void imprimir_entero_grande(FILE *salida, const EnteroGrande *num) {
    fprintf(salida, "%u", num->digitos[num->longitud - 1]);
    for (int i = num->longitud - 2; i >= 0; i--)
        fprintf(salida, "%09u", num->digitos[i]);
}

static int es_cero(const EnteroGrande *num) { return num->longitud == 1 && num->digitos[0] == 0; }
static int es_uno (const EnteroGrande *num) { return num->longitud == 1 && num->digitos[0] == 1; }

/* ---------------------------------------------------------------------------
 * FUNCIONES DEL POLINOMIO Y PASCAL
 * -------------------------------------------------------------------------*/
static EnteroGrande *construir_fila_pascal(int n) {
    EnteroGrande *fila = (EnteroGrande *)malloc((n + 1) * sizeof(EnteroGrande));
    for (int i = 0; i <= n; i++) inicializar_entero_grande(&fila[i], 4);

    asignar_valor_pequeno(&fila[0], 1);
    EnteroGrande temp;
    inicializar_entero_grande(&temp, 4);

    for (int k = 1; k <= n; k++) {
        for (int j = k; j >= 1; j--) {
            sumar_enteros(&temp, &fila[j], &fila[j - 1]);
            EnteroGrande t = fila[j];
            fila[j] = temp;
            temp = t;
        }
    }
    liberar_entero_grande(&temp);
    return fila;
}

static void liberar_fila_pascal(EnteroGrande *fila, int n) {
    for (int i = 0; i <= n; i++) liberar_entero_grande(&fila[i]);
    free(fila);
}

static void imprimir_polinomio(FILE *salida, const EnteroGrande *coeficientes, int n) {
    int primero = 1;
    for (int i = n; i >= 0; i--) {
        const EnteroGrande *c = &coeficientes[i];
        if (es_cero(c)) continue;
        int es_un_uno = es_uno(c);

        if (!primero) fprintf(salida, " + ");
        primero = 0;

        if (i == 0) {
            imprimir_entero_grande(salida, c);
        } else if (i == 1) {
            if (!es_un_uno) imprimir_entero_grande(salida, c);
            fprintf(salida, "x");
        } else {
            if (!es_un_uno) imprimir_entero_grande(salida, c);
            fprintf(salida, "x^%d", i);
        }
    }
    if (primero) fprintf(salida, "0");
}

static void evaluar_paso_a_paso(FILE *salida, const EnteroGrande *coeficientes, int n, unsigned long long x) {
    EnteroGrande total, potencia, termino, siguiente_potencia;
    inicializar_entero_grande(&total, 4);
    inicializar_entero_grande(&potencia, 4);
    inicializar_entero_grande(&termino, 4);
    inicializar_entero_grande(&siguiente_potencia, 4);

    asignar_valor_pequeno(&total, 0);
    asignar_valor_pequeno(&potencia, 1);

    EnteroGrande x_grande;
    inicializar_entero_grande(&x_grande, 4);
    asignar_valor_pequeno(&x_grande, x);

    for (int i = 0; i <= n; i++) {
        multiplicar_enteros(&termino, &coeficientes[i], &potencia);
        EnteroGrande siguiente_total;
        inicializar_entero_grande(&siguiente_total, 4);
        sumar_enteros(&siguiente_total, &total, &termino);
        liberar_entero_grande(&total);
        total = siguiente_total;

        fprintf(salida, "Paso %d: c_%d * x^%d = ", i, i, i);
        imprimir_entero_grande(salida, &coeficientes[i]);
        fprintf(salida, " * ");
        imprimir_entero_grande(salida, &potencia);
        fprintf(salida, " = ");
        imprimir_entero_grande(salida, &termino);
        fprintf(salida, "\n");

        if (i < n) {
            multiplicar_enteros(&siguiente_potencia, &potencia, &x_grande);
            EnteroGrande t = potencia;
            potencia = siguiente_potencia;
            siguiente_potencia = t;
        }
    }

    fprintf(salida, "f(%llu) = ", x);
    imprimir_entero_grande(salida, &total);
    fprintf(salida, "\n");

    liberar_entero_grande(&total);
    liberar_entero_grande(&potencia);
    liberar_entero_grande(&termino);
    liberar_entero_grande(&siguiente_potencia);
    liberar_entero_grande(&x_grande);
}

/* ---------------------------------------------------------------------------
 * FUNCIÓN PRINCIPAL
 * -------------------------------------------------------------------------*/
int main(void) {
    FILE *archivo = fopen("resultado_ej2_c.txt", "w");
    if (!archivo) {
        printf("Error al crear el archivo de reporte.\n");
        return 1;
    }

    /* Encabezado del reporte */
    fprintf(archivo, "UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n");
    fprintf(archivo, "PRUEBA DIAGNOSTICA - LENGUAJES Y COMPILADORES\n");
    fprintf(archivo, "EJERCICIO 2: POLINOMIO (X+1)^N Y EVALUACION (LENGUAJE C)\n");
    fprintf(archivo, "======================================================================\n\n");

    /* Demostración con n=5 y x=2 */
    int n_demo = 5;
    unsigned long long x_demo = 2;
    
    fprintf(archivo, "RESULTADO DE LA DEMOSTRACION (n=%d, x=%llu):\n\n", n_demo, x_demo);
    EnteroGrande *coef_demo = construir_fila_pascal(n_demo);
    
    fprintf(archivo, "a) Polinomio generado:\n");
    fprintf(archivo, "(x+1)^%d = ", n_demo);
    imprimir_polinomio(archivo, coef_demo, n_demo);
    fprintf(archivo, "\nCoeficientes (Pascal): ");
    for (int i = 0; i <= n_demo; i++) {
        imprimir_entero_grande(archivo, &coef_demo[i]);
        if (i < n_demo) fprintf(archivo, " ");
    }
    fprintf(archivo, "\n\nb) Evaluacion paso a paso para x = %llu:\n", x_demo);
    evaluar_paso_a_paso(archivo, coef_demo, n_demo, x_demo);
    liberar_fila_pascal(coef_demo, n_demo);

    /* Medición n=100 */
    fprintf(archivo, "\n======================================================================\n");
    fprintf(archivo, "REPORTE DE MEDICION DE TIEMPOS DE EJECUCION:\n");
    fprintf(archivo, "Generacion del polinomio para n = 100\n");
    fprintf(archivo, "Repeticiones: 100\n\n");

    clock_t inicio = clock();
    for (int r = 0; r < 100; r++) {
        EnteroGrande *fila = construir_fila_pascal(100);
        liberar_fila_pascal(fila, 100);
    }
    clock_t fin = clock();

    double total_ms = 1000.0 * (double)(fin - inicio) / CLOCKS_PER_SEC;
    double promedio_ms = total_ms / 100.0;

    fprintf(archivo, "Tiempo total (C)    : %.6f ms\n", total_ms);
    fprintf(archivo, "Tiempo promedio (C) : %.6f ms\n", promedio_ms);

    fclose(archivo);
    printf("Ejecucion en C finalizada. Revisar 'resultado_ej2_c.txt'\n");
    return 0;
}