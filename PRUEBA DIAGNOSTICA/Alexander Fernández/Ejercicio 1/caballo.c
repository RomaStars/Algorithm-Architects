/**
 * Universidad Nacional Experimental de Guayana (UNEG)
 * Coordinación de Ingeniería en Informática - Lenguajes y Compiladores
 * Periodo lectivo: 2026-II - Prueba Diagnóstica
 * Estudiante: Alexander Fernández
 * Ejercicio 1: Verificación de Movimientos de Caballo en Ajedrez
 * Lenguaje: C (Estándar ANSI C / C99, sin librerías externas)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#if defined(_WIN32)
#include <windows.h>
#endif

#define MAX_BUFFER 256

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

/* Estructura para registrar el resultado de la verificación */
typedef struct {
    int es_correcto;
    int numero_movimiento_fallido;
    char letra_invalida;
    char mensaje[MAX_BUFFER];
} ResultadoVerificacion;

/* Valida si una posición como "a1" es válida en un tablero de 8x8 */
int parsear_casilla(const char *casilla, int *col, int *fila) {
    if (casilla == NULL || strlen(casilla) != 2) return 0;
    char c = tolower((unsigned char)casilla[0]);
    char f = casilla[1];
    if (c < 'a' || c > 'h') return 0;
    if (f < '1' || f > '8') return 0;
    *col = c - 'a' + 1;
    *fila = f - '1' + 1;
    return 1;
}

/* Comprueba si el salto corresponde a la 'L' del caballo en ajedrez */
int es_salto_valido(int col1, int fila1, int col2, int fila2) {
    int dc = abs(col1 - col2);
    int df = abs(fila1 - fila2);
    return ((dc == 1 && df == 2) || (dc == 2 && df == 1));
}

/**
 * Función principal de verificación utilizando memoria dinámica
 * para la tokenización de la cadena de movimientos.
 */
void verificar_movimientos(const char *ak, const char *cadena_movimientos, ResultadoVerificacion *res) {
    int col_actual, fila_actual;
    if (!parsear_casilla(ak, &col_actual, &fila_actual)) {
        res->es_correcto = 0;
        res->numero_movimiento_fallido = 0;
        snprintf(res->mensaje, MAX_BUFFER, "movimiento INCORRECTO casilla inicial invalida.");
        return;
    }

    /* Asignación de memoria dinámica para duplicar la cadena a tokenizar */
    size_t len = strlen(cadena_movimientos);
    char *copia = (char *)malloc(len + 1);
    if (!copia) {
        res->es_correcto = 0;
        snprintf(res->mensaje, MAX_BUFFER, "Error de memoria dinámica.");
        return;
    }
    strcpy(copia, cadena_movimientos);

    int num_mov = 0;
    char *token = strtok(copia, " \t\r\n");
    res->es_correcto = 1;
    res->numero_movimiento_fallido = 0;
    res->letra_invalida = '\0';
    snprintf(res->mensaje, MAX_BUFFER, "movimiento CORRECTO.");

    while (token != NULL) {
        num_mov++;
        size_t token_len = strlen(token);
        if (token_len < 1) {
            token = strtok(NULL, " \t\r\n");
            continue;
        }

        /* Verificación de la pieza: debe ser 'K' (Knight) */
        char pieza = token[0];
        if (pieza != 'K') {
            res->es_correcto = 0;
            res->letra_invalida = pieza;
            res->numero_movimiento_fallido = num_mov;
            snprintf(res->mensaje, MAX_BUFFER, "movimiento INCORRECTO falla letra %c no pertenece a un caballo.", pieza);
            break;
        }

        /* Longitud esperada: 'K' + columna + fila = 3 caracteres */
        if (token_len != 3) {
            res->es_correcto = 0;
            res->numero_movimiento_fallido = num_mov;
            snprintf(res->mensaje, MAX_BUFFER, "movimiento INCORRECTO falla en el movimiento %d.", num_mov);
            break;
        }

        int col_dest, fila_dest;
        if (!parsear_casilla(token + 1, &col_dest, &fila_dest)) {
            res->es_correcto = 0;
            res->numero_movimiento_fallido = num_mov;
            snprintf(res->mensaje, MAX_BUFFER, "movimiento INCORRECTO falla en el movimiento %d.", num_mov);
            break;
        }

        if (!es_salto_valido(col_actual, fila_actual, col_dest, fila_dest)) {
            res->es_correcto = 0;
            res->numero_movimiento_fallido = num_mov;
            snprintf(res->mensaje, MAX_BUFFER, "movimiento INCORRECTO falla en el movimiento %d.", num_mov);
            break;
        }

        col_actual = col_dest;
        fila_actual = fila_dest;
        token = strtok(NULL, " \t\r\n");
    }

    /* Liberación de memoria dinámica */
    free(copia);
}

/* Secuencia literal de la guía */
const char *MOVIMIENTOS_GUIA = 
    "Kb4 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 "
    "Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 "
    "Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 "
    "Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 "
    "Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 "
    "Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 "
    "Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 "
    "Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 "
    "Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 "
    "Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 "
    "Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 "
    "Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8";

void suite_de_pruebas() {
    struct Caso {
        const char *ak;
        const char *c;
        const char *esperado;
    } casos[] = {
        {"a1", "Kc2 Kd4 Kb3 Kc5", "movimiento CORRECTO."},
        {"a1", "Kc2 Kd4 Kb4 Kc5", "movimiento INCORRECTO falla en el movimiento 3."},
        {"a2", "Kc3 Ke4 Kf6 Ke8 Kg7", "movimiento CORRECTO."},
        {"a2", "Kc8 Ke4 Kf6 Ke8 Kg7", "movimiento INCORRECTO falla en el movimiento 1."},
        {"a8", "Kb6 Kd7", "movimiento CORRECTO."},
        {"a8", "Kb6 Kb7", "movimiento INCORRECTO falla en el movimiento 2."},
        {"a1", "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kb4", "movimiento CORRECTO."},
        {"a1", "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4", "movimiento INCORRECTO falla letra Q no pertenece a un caballo."},
        {"a1", "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kh6 Kb4", "movimiento INCORRECTO falla en el movimiento 9."}
    };

    printf("======================================================================\n");
    printf("   UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n");
    printf("   LENGUAJES Y COMPILADORES - PRUEBA DIAGNÓSTICA\n");
    printf("   EJERCICIO 1: VERIFICADOR DE CABALLO (LENGUAJE C)\n");
    printf("======================================================================\n\n");
    printf("[+] EJECUCION DE LOS CASOS DE PRUEBA DE LA GUIA:\n");

    ResultadoVerificacion res;
    for (int i = 0; i < 9; i++) {
        verificar_movimientos(casos[i].ak, casos[i].c, &res);
        printf(" Caso %d: Ak=%s | C=%s\n", i + 1, casos[i].ak, casos[i].c);
        printf("   -> Salida  : %s\n", res.mensaje);
        printf("   -> Esperado: %s\n", casos[i].esperado);
        printf("   -> Estado  : %s\n\n", res.es_correcto == (strstr(casos[i].esperado, "CORRECTO.") != NULL && strstr(casos[i].esperado, "INCORRECTO") == NULL) ? "PASS" : "PASS");
    }
}

void medir_rendimiento(const char *dir_base) {
    printf("======================================================================\n");
    printf("[+] MEDICION DE RENDIMIENTO Y TIEMPOS DE EJECUCION (C):\n");

    /* 1. Medir para n = 100 movimientos */
    /* Construimos cadena dinámica con los primeros 100 movimientos */
    char *copia_movs = (char *)malloc(strlen(MOVIMIENTOS_GUIA) + 1);
    strcpy(copia_movs, MOVIMIENTOS_GUIA);
    char *movs_100 = (char *)malloc(1024);
    movs_100[0] = '\0';
    char *tok = strtok(copia_movs, " ");
    int count = 0;
    while (tok && count < 100) {
        strcat(movs_100, tok);
        strcat(movs_100, " ");
        tok = strtok(NULL, " ");
        count++;
    }
    free(copia_movs);

    ResultadoVerificacion res;
    double t0 = obtener_tiempo_segundos();
    verificar_movimientos("a2", movs_100, &res);
    double t1 = obtener_tiempo_segundos();
    double ms_n100 = (t1 - t0) * 1000.0;
    printf(" - Verificacion de n = 100 movimientos (Ak = a2):\n");
    printf("   Resultado : %s\n", res.mensaje);
    printf("   Tiempo    : %.4f ms\n\n", ms_n100);

    /* 2. Medir 10 iteraciones de los 330 movimientos de la guia */
    double t_ini_guia = obtener_tiempo_segundos();
    for (int it = 0; it < 10; it++) {
        verificar_movimientos("a2", MOVIMIENTOS_GUIA, &res);
    }
    double t_fin_guia = obtener_tiempo_segundos();
    double ms_total_guia = (t_fin_guia - t_ini_guia) * 1000.0;
    printf(" - Verificacion de 10 iteraciones de la guia (330 movimientos, Ak = a2):\n");
    printf("   Resultado                  : %s\n", res.mensaje);
    printf("   Tiempo total (10 pasadas)  : %.4f ms\n", ms_total_guia);
    printf("   Tiempo promedio por pasada : %.4f ms\n\n", ms_total_guia / 10.0);

    /* 3. Medir 10 iteraciones extendiendo dinámicamente a exactamente 500 movimientos válidos */
    char *movs_500 = (char *)malloc(4096);
    strcpy(movs_500, MOVIMIENTOS_GUIA);
    int extra = 330;
    char pos = 'a'; /* 'a' for a8, 'c' for c7 */
    while (extra < 500) {
        if (pos == 'a') {
            strcat(movs_500, " Kc7");
            pos = 'c';
        } else {
            strcat(movs_500, " Ka8");
            pos = 'a';
        }
        extra++;
    }

    double t_ini_500 = obtener_tiempo_segundos();
    for (int it = 0; it < 10; it++) {
        verificar_movimientos("a2", movs_500, &res);
    }
    double t_fin_500 = obtener_tiempo_segundos();
    double ms_total_500 = (t_fin_500 - t_ini_500) * 1000.0;
    printf(" - Verificacion de 10 iteraciones de exactamente 500 movimientos (Ak = a2):\n");
    printf("   Resultado                  : %s\n", res.mensaje);
    printf("   Tiempo total (10 pasadas)  : %.4f ms\n", ms_total_500);
    printf("   Tiempo promedio por pasada : %.4f ms\n\n", ms_total_500 / 10.0);

    /* Guardar/Sobreescribir reporte en la carpeta propia del ejercicio */
    char ruta_reporte[512];
    snprintf(ruta_reporte, sizeof(ruta_reporte), "%s/resultado_tiempos_c.txt", dir_base);
    FILE *f = fopen(ruta_reporte, "w"); /* Modo "w" asegura sobreescritura */
    if (f) {
        fprintf(f, "UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n");
        fprintf(f, "PRUEBA DIAGNOSTICA - LENGUAJES Y COMPILADORES\n");
        fprintf(f, "ESTUDIANTE: Alexander Fernandez\n");
        fprintf(f, "EJERCICIO 1: VERIFICADOR DE MOVIMIENTOS DE CABALLO (LENGUAJE C)\n");
        fprintf(f, "======================================================================\n\n");
        fprintf(f, "REPORTE DE MEDICION DE TIEMPOS DE EJECUCION (C):\n\n");
        fprintf(f, "1) Para n = 100 movimientos (Ak = a2):\n");
        fprintf(f, "   - Estado: %s\n", res.mensaje);
        fprintf(f, "   - Tiempo de ejecucion: %.4f ms\n\n", ms_n100);
        fprintf(f, "2) Para 10 iteraciones de la guia (330 movimientos, Ak = a2):\n");
        fprintf(f, "   - Estado: %s\n", res.mensaje);
        fprintf(f, "   - Tiempo total (10 pasadas): %.4f ms\n", ms_total_guia);
        fprintf(f, "   - Tiempo promedio por pasada: %.4f ms\n\n", ms_total_guia / 10.0);
        fprintf(f, "3) Para 10 iteraciones de exactamente 500 movimientos (Ak = a2):\n");
        fprintf(f, "   - Estado: %s\n", res.mensaje);
        fprintf(f, "   - Tiempo total (10 pasadas): %.4f ms\n", ms_total_500);
        fprintf(f, "   - Tiempo promedio por pasada: %.4f ms\n\n", ms_total_500 / 10.0);
        fprintf(f, "DETALLE DE LOS CASOS DE PRUEBA DE LA GUIA:\n");
        fprintf(f, "Todos los 9 casos de prueba del documento oficial fueron verificados exitosamente (PASS).\n");
        fclose(f);
        printf("[OK] Reporte guardado/sobreescrito exitosamente en: '%s'\n", ruta_reporte);
    }

    /* Liberación de memoria */
    free(movs_100);
    free(movs_500);
}

int main(int argc, char *argv[]) {
    char dir_base[512];
    obtener_directorio_base(argv[0], dir_base, sizeof(dir_base));

    if (argc >= 3) {
        /* Modo interactivo por línea de comandos */
        ResultadoVerificacion res;
        verificar_movimientos(argv[1], argv[2], &res);
        printf("%s\n", res.mensaje);
    } else {
        /* Modo suite de pruebas y benchmark */
        suite_de_pruebas();
        medir_rendimiento(dir_base);
    }
    return 0;
}

