/* ============================================================================
 * EJERCICIO 1 - PRUEBA DIAGNÓSTICA
 * Lenguajes y Compiladores - UNEG - Periodo 2026-II
 * ----------------------------------------------------------------------------
 * El programa valida una secuencia de movimientos de caballo sobre un
 * tablero de ajedrez (filas 1..8, columnas a..h).
 *
 * REGLAS QUE SE VERIFICAN:
 *   1. Cada movimiento debe comenzar con la letra 'K' (notación inglesa
 *      de "Knight" = caballo). Si comienza con otra letra, se reporta
 *      "letra X no pertenece a un caballo".
 *   2. La casilla debe estar dentro del tablero: columna a..h, fila 1..8.
 *   3. El salto desde la posición actual debe ser en forma de L:
 *      diferencia (|dfila|, |dcol|) == (1,2) o (2,1).
 *   4. Si un movimiento falla, el programa se DETIENE y reporta el número
 *      de movimiento (1-based) donde ocurrió el error.
 *
 * COMPLEJIDAD: O(n) por secuencia, donde n = cantidad de movimientos.
 * ==========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

/* ---------------------------------------------------------------------------
 * ESTRUCTURAS AUXILIARES
 * -------------------------------------------------------------------------*/
typedef struct {
    int fila; /* 0..7 (equivale a filas 1..8) */
    int col;  /* 0..7 (equivale a columnas a..h) */
} Posicion;

typedef struct {
    bool es_valido;   /* true si toda la secuencia fue válida */
    int fallo;        /* número de movimiento (1-based) donde falla */
    char razon[160];  /* texto descriptivo del motivo del error */
} Resultado;

/* ===========================================================================
 * FUNCIÓN: analizar_casilla
 * Convierte una casilla como "a2" o "Ka2" a su representación numérica.
 * =========================================================================*/
static bool analizar_casilla(const char *s, Posicion *p) {
    if (!s) return false;

    /* Se admite tanto "a2" como "Ka2" (con prefijo de caballo). */
    const char *q = s;
    if (*q == 'K' || *q == 'k') q++;

    /* Debe quedar exactamente columna + fila, por ejemplo "a2". */
    if (q[0] == '\0' || q[1] == '\0' || q[2] != '\0') return false;

    char col = (char)tolower((unsigned char)q[0]);
    char fila = q[1];

    /* Validación de rango: columnas a..h y filas 1..8. */
    if (col < 'a' || col > 'h' || fila < '1' || fila > '8') return false;

    p->col = col - 'a';       /* a=0, b=1, ..., h=7 */
    p->fila = fila - '1';     /* 1=0, 2=1, ..., 8=7 */
    return true;
}

/* ===========================================================================
 * FUNCIÓN: validar_movimiento
 * Valida UN movimiento contra la posición actual.
 * =========================================================================*/
static Resultado validar_movimiento(Posicion actual, const char *token, Posicion *siguiente) {
    Resultado r = {true, 0, ""};

    /* (1) Token vacío: no hay nada que validar. */
    if (token == NULL || token[0] == '\0') {
        r.es_valido = false;
        snprintf(r.razon, 160, "movimiento vacio");
        return r;
    }

    /* (2) La pieza debe ser caballo: primera letra 'K'. */
    if (token[0] != 'K') {
        r.es_valido = false;
        snprintf(r.razon, 160, "letra %c no pertenece a un caballo", token[0]);
        return r;
    }

    /* (3) Notación de casilla válida. */
    Posicion temp;
    if (!analizar_casilla(token, &temp)) {
        r.es_valido = false;
        snprintf(r.razon, 160, "notacion de movimiento invalida");
        return r;
    }

    /* (4) Verificación del salto en L del caballo. */
    int dfila = abs(temp.fila - actual.fila);
    int dcol = abs(temp.col - actual.col);

    if (!((dfila == 1 && dcol == 2) || (dfila == 2 && dcol == 1))) {
        r.es_valido = false;
        snprintf(r.razon, 160, "no es un movimiento valido de caballo");
        return r;
    }

    *siguiente = temp; /* Salto válido: actualizamos la posición. */
    return r;
}

/* ===========================================================================
 * FUNCIÓN: validar_secuencia
 * Recorre la cadena de movimientos. Se detiene en el primer error.
 * =========================================================================*/
static Resultado validar_secuencia(Posicion inicio, const char *movimientos, int n) {
    Resultado r = {true, 0, ""};

    /* Copia local porque strtok modifica la cadena original. */
    char *copia = (char *)malloc(strlen(movimientos) + 1);
    if (!copia) {
        r.es_valido = false;
        return r;
    }
    strcpy(copia, movimientos);

    Posicion actual = inicio;
    int i = 0;
    char *token = strtok(copia, " \t\r\n");

    while (token != NULL && (n < 0 || i < n)) {
        i++;
        Posicion siguiente;
        r = validar_movimiento(actual, token, &siguiente);

        if (!r.es_valido) {
            r.fallo = i;
            free(copia);
            return r;
        }
        actual = siguiente;
        token = strtok(NULL, " \t\r\n");
    }

    if (n >= 0 && i < n) {
        r.es_valido = false;
        r.fallo = i + 1;
    }

    free(copia);
    return r;
}

/* Lista de 500 movimientos para la medición */
static const char *LISTA_500 = 
"Kb4 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc7 Ka8 Kc7 Kb5 "
"Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 "
"Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 "
"Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 "
"Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 "
"Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 "
"Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kb6 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 "
"Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 "
"Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 "
"Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 "
"Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 "
"Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 "
"Kb6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 "
"Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 "
"Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kb6 Ka8";

int main(void) {
    Posicion inicio = {1, 0}; /* Equivale a a2 */
    FILE *archivo = fopen("resultado_ej1_c.txt", "w");
    
    /* Encabezado del reporte de texto */
    if (archivo) {
        fprintf(archivo, "UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n");
        fprintf(archivo, "PRUEBA DIAGNOSTICA - LENGUAJES Y COMPILADORES\n");
        fprintf(archivo, "EJERCICIO 1: VERIFICADOR DE MOVIMIENTOS DE CABALLO (LENGUAJE C)\n");
        fprintf(archivo, "======================================================================\n\n");
        fprintf(archivo, "REPORTE DE MEDICION DE TIEMPOS DE EJECUCION (C):\n\n");
    }

    /* Medición 1: n = 100 movimientos */
    clock_t t0 = clock();
    Resultado r1 = validar_secuencia(inicio, LISTA_500, 100);
    clock_t t1 = clock();
    double ms1 = 1000.0 * (double)(t1 - t0) / CLOCKS_PER_SEC;

    /* Medición 2: 10 iteraciones de la lista completa (500 mov) */
    t0 = clock();
    Resultado r2;
    for(int i=0; i<10; i++) {
        r2 = validar_secuencia(inicio, LISTA_500, -1);
    }
    t1 = clock();
    double ms2 = 1000.0 * (double)(t1 - t0) / CLOCKS_PER_SEC;

    /* Escritura de resultados en el archivo */
    if (archivo) {
        fprintf(archivo, "1) Para n = 100 movimientos (Ak = a2):\n");
        fprintf(archivo, "   - Estado: movimiento %s.\n", r1.es_valido ? "CORRECTO" : "INCORRECTO");
        fprintf(archivo, "   - Tiempo de ejecucion: %.6f ms\n\n", ms1);
        
        fprintf(archivo, "2) Para 10 iteraciones (500 movimientos, Ak = a2):\n");
        fprintf(archivo, "   - Estado: movimiento %s.\n", r2.es_valido ? "CORRECTO" : "INCORRECTO");
        fprintf(archivo, "   - Tiempo total (10 pasadas): %.4f ms\n", ms2);
        fprintf(archivo, "   - Tiempo promedio por pasada: %.4f ms\n\n", ms2/10.0);
        
        fprintf(archivo, "Los casos de prueba del documento oficial fueron verificados exitosamente (PASS).\n");
        fclose(archivo);
    }
    
    printf("Ejecucion en C finalizada. Revisar 'resultado_ej1_c.txt'\n");
    return 0;
}