/**
 * Universidad Nacional Experimental de Guayana (UNEG)
 * Coordinación de Ingeniería en Informática - Lenguajes y Compiladores
 * Periodo lectivo: 2026-II - Prueba Diagnóstica
 * Estudiante: Alexander Fernández
 * Ejercicio 3: Analizador Léxico y Traductor de Palabras Reservadas de C a Español
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

#define NUM_KEYWORDS 37

typedef struct {
    const char *en;
    const char *es;
    int conteo;
} KeywordMapping;

KeywordMapping TABLA_KEYWORDS[NUM_KEYWORDS] = {
    {"auto", "auto", 0},
    {"break", "interrumpir", 0},
    {"case", "caso", 0},
    {"char", "caracter", 0},
    {"const", "constante", 0},
    {"continue", "continuar", 0},
    {"default", "defecto", 0},
    {"do", "hacer", 0},
    {"double", "doble", 0},
    {"else", "sino", 0},
    {"enum", "enumeracion", 0},
    {"extern", "externo", 0},
    {"float", "flotante", 0},
    {"for", "para", 0},
    {"goto", "ira", 0},
    {"if", "si", 0},
    {"inline", "enlinea", 0},
    {"int", "entero", 0},
    {"long", "largo", 0},
    {"register", "registro", 0},
    {"restrict", "restringido", 0},
    {"return", "retornar", 0},
    {"short", "corto", 0},
    {"signed", "con_signo", 0},
    {"sizeof", "tamano_de", 0},
    {"static", "estatico", 0},
    {"struct", "estructura", 0},
    {"switch", "segun", 0},
    {"typedef", "definir_tipo", 0},
    {"union", "union", 0},
    {"unsigned", "sin_signo", 0},
    {"void", "vacio", 0},
    {"volatile", "volatil", 0},
    {"while", "mientras", 0},
    {"_Bool", "_Booleano", 0},
    {"_Complex", "_Complejo", 0},
    {"_Imaginary", "_Imaginario", 0}
};

/* Busca si un token coincide con alguna palabra reservada de C */
const char* buscar_traduccion(const char *token) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(TABLA_KEYWORDS[i].en, token) == 0) {
            TABLA_KEYWORDS[i].conteo++;
            return TABLA_KEYWORDS[i].es;
        }
    }
    return NULL;
}

/**
 * Carga un archivo completo en un búfer de memoria dinámica.
 * Retorna el puntero al búfer asignado con malloc, o NULL en caso de error.
 */
char* cargar_archivo_dinamico(const char *ruta, long *tamano_bytes) {
    FILE *f = fopen(ruta, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buf = (char *)malloc(tam + 1);
    if (!buf) {
        fclose(f);
        return NULL;
    }

    size_t leidos = fread(buf, 1, tam, f);
    buf[leidos] = '\0';
    fclose(f);

    if (tamano_bytes) *tamano_bytes = (long)leidos;
    return buf;
}

/**
 * Analizador léxico que recorre el código fuente en memoria dinámica
 * respetando cadenas, comentarios e identificadores.
 */
char* traducir_codigo_c(const char *fuente, size_t tam_fuente) {
    /* Capacidad dinámica estimada para el código traducido */
    size_t cap = tam_fuente * 2 + 4096;
    char *salida = (char *)malloc(cap);
    if (!salida) return NULL;

    size_t i = 0;
    size_t pos_salida = 0;

    #define APPEND_CHAR(ch) do { \
        if (pos_salida + 1 >= cap) { \
            cap *= 2; \
            salida = (char *)realloc(salida, cap); \
        } \
        salida[pos_salida++] = (ch); \
    } while(0)

    #define APPEND_STR(str) do { \
        size_t slen = strlen(str); \
        while (pos_salida + slen >= cap) { \
            cap *= 2; \
            salida = (char *)realloc(salida, cap); \
        } \
        memcpy(salida + pos_salida, str, slen); \
        pos_salida += slen; \
    } while(0)

    while (i < tam_fuente) {
        char c = fuente[i];

        /* 1. Comentarios de una sola línea: // ... */
        if (c == '/' && i + 1 < tam_fuente && fuente[i + 1] == '/') {
            while (i < tam_fuente && fuente[i] != '\n') {
                APPEND_CHAR(fuente[i]);
                i++;
            }
            continue;
        }

        /* 2. Comentarios multilínea: /* ... * / */
        if (c == '/' && i + 1 < tam_fuente && fuente[i + 1] == '*') {
            APPEND_CHAR(fuente[i++]);
            APPEND_CHAR(fuente[i++]);
            while (i + 1 < tam_fuente && !(fuente[i] == '*' && fuente[i + 1] == '/')) {
                APPEND_CHAR(fuente[i]);
                i++;
            }
            if (i + 1 < tam_fuente) {
                APPEND_CHAR(fuente[i++]);
                APPEND_CHAR(fuente[i++]);
            }
            continue;
        }

        /* 3. Literales de cadena: " ... " */
        if (c == '"') {
            APPEND_CHAR(fuente[i++]);
            while (i < tam_fuente) {
                if (fuente[i] == '\\' && i + 1 < tam_fuente) {
                    APPEND_CHAR(fuente[i++]);
                    APPEND_CHAR(fuente[i++]);
                } else if (fuente[i] == '"') {
                    APPEND_CHAR(fuente[i++]);
                    break;
                } else {
                    APPEND_CHAR(fuente[i++]);
                }
            }
            continue;
        }

        /* 4. Literales de carácter: ' ... ' */
        if (c == '\'') {
            APPEND_CHAR(fuente[i++]);
            while (i < tam_fuente) {
                if (fuente[i] == '\\' && i + 1 < tam_fuente) {
                    APPEND_CHAR(fuente[i++]);
                    APPEND_CHAR(fuente[i++]);
                } else if (fuente[i] == '\'') {
                    APPEND_CHAR(fuente[i++]);
                    break;
                } else {
                    APPEND_CHAR(fuente[i++]);
                }
            }
            continue;
        }

        /* 5. Identificadores y palabras reservadas */
        if (isalpha((unsigned char)c) || c == '_') {
            size_t inicio = i;
            while (i < tam_fuente && (isalnum((unsigned char)fuente[i]) || fuente[i] == '_')) {
                i++;
            }
            size_t token_len = i - inicio;
            char token[128];
            if (token_len < sizeof(token)) {
                memcpy(token, fuente + inicio, token_len);
                token[token_len] = '\0';
                const char *trad = buscar_traduccion(token);
                if (trad) {
                    APPEND_STR(trad);
                } else {
                    APPEND_STR(token);
                }
            } else {
                for (size_t k = inicio; k < i; k++) {
                    APPEND_CHAR(fuente[k]);
                }
            }
            continue;
        }

        /* 6. Otros caracteres */
        APPEND_CHAR(c);
        i++;
    }

    salida[pos_salida] = '\0';
    return salida;
}

int main(int argc, char *argv[]) {
    char dir_base[512];
    obtener_directorio_base(argv[0], dir_base, sizeof(dir_base));

    char ruta_entrada[512];
    char ruta_salida[512];
    char ruta_reporte[512];

    if (argc >= 2) {
        strncpy(ruta_entrada, argv[1], sizeof(ruta_entrada));
    } else {
        snprintf(ruta_entrada, sizeof(ruta_entrada), "%s/programa_prueba.c", dir_base);
    }

    if (argc >= 3) {
        strncpy(ruta_salida, argv[2], sizeof(ruta_salida));
    } else {
        snprintf(ruta_salida, sizeof(ruta_salida), "%s/programa_traducido_c.c", dir_base);
    }

    snprintf(ruta_reporte, sizeof(ruta_reporte), "%s/resultado_traduccion_c.txt", dir_base);

    printf("======================================================================\n");
    printf("   UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n");
    printf("   LENGUAJES Y COMPILADORES - PRUEBA DIAGNOSTICA\n");
    printf("   EJERCICIO 3: ANALIZADOR Y TRADUCTOR DE PALABRAS RESERVADAS (C)\n");
    printf("======================================================================\n\n");

    printf("[+] Cargando archivo dinamicamente en memoria: '%s'...\n", ruta_entrada);
    long tamano_bytes = 0;
    double t0 = obtener_tiempo_segundos();
    char *codigo = cargar_archivo_dinamico(ruta_entrada, &tamano_bytes);
    double t1 = obtener_tiempo_segundos();

    if (!codigo) {
        fprintf(stderr, "Error: No se pudo abrir o leer el archivo '%s'\n", ruta_entrada);
        return 1;
    }

    double tiempo_carga_ms = (t1 - t0) * 1000.0;
    printf(" [OK] Archivo cargado exitosamente. Tamano en memoria: %ld bytes (%.4f ms)\n",
           tamano_bytes, tiempo_carga_ms);

    printf("\n[+] Ejecutando escaneo lexico y traduccion en memoria dinamica...\n");
    double t2 = obtener_tiempo_segundos();
    char *traducido = traducir_codigo_c(codigo, (size_t)tamano_bytes);
    double t3 = obtener_tiempo_segundos();
    double tiempo_analisis_ms = (t3 - t2) * 1000.0;

    if (!traducido) {
        fprintf(stderr, "Error durante la traduccion en memoria dinamica.\n");
        free(codigo);
        return 1;
    }

    printf(" [OK] Analisis lexico completado en %.4f ms.\n\n", tiempo_analisis_ms);
    printf("[+] DETALLE DE PALABRAS RESERVADAS IDENTIFICADAS Y TRADUCIDAS:\n");
    printf("----------------------------------------------------------------------\n");
    printf("%-4s %-15s %-20s %-12s\n", "#", "Palabra C", "Traduccion Espanol", "Frecuencia");
    printf("----------------------------------------------------------------------\n");

    int idx = 1;
    int total_encontradas = 0;
    int unicas = 0;
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (TABLA_KEYWORDS[i].conteo > 0) {
            printf("%-4d %-15s %-20s %-12d\n",
                   idx++, TABLA_KEYWORDS[i].en, TABLA_KEYWORDS[i].es, TABLA_KEYWORDS[i].conteo);
            total_encontradas += TABLA_KEYWORDS[i].conteo;
            unicas++;
        }
    }
    printf("----------------------------------------------------------------------\n");
    printf("Total de palabras reservadas detectadas: %d (unicas: %d)\n\n", total_encontradas, unicas);

    /* Guardar/Sobreescribir archivo traducido */
    FILE *fout = fopen(ruta_salida, "wb");
    if (fout) {
        fwrite(traducido, 1, strlen(traducido), fout);
        fclose(fout);
        printf("[OK] Codigo traducido guardado/sobreescrito en: '%s'\n", ruta_salida);
    }

    /* Guardar/Sobreescribir informe de resultados en la carpeta del ejercicio */
    FILE *frep = fopen(ruta_reporte, "w");
    if (frep) {
        fprintf(frep, "UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n");
        fprintf(frep, "PRUEBA DIAGNOSTICA - LENGUAJES Y COMPILADORES\n");
        fprintf(frep, "ESTUDIANTE: Alexander Fernandez\n");
        fprintf(frep, "EJERCICIO 3: ANALIZADOR Y TRADUCTOR DE PALABRAS RESERVADAS EN C\n");
        fprintf(frep, "======================================================================\n\n");
        fprintf(frep, "Archivo analizado : %s\n", ruta_entrada);
        fprintf(frep, "Tamano dinamico   : %ld bytes\n", tamano_bytes);
        fprintf(frep, "Tiempo de carga   : %.4f ms\n", tiempo_carga_ms);
        fprintf(frep, "Tiempo de analisis: %.4f ms\n\n", tiempo_analisis_ms);
        fprintf(frep, "RESUMEN DE PALABRAS RESERVADAS ENCONTRADAS:\n");
        fprintf(frep, "- Palabras distintas encontradas: %d\n", unicas);
        fprintf(frep, "- Total de ocurrencias           : %d\n\n", total_encontradas);
        fprintf(frep, "%-4s %-15s %-20s %-12s\n", "#", "Palabra C", "Traduccion Espanol", "Frecuencia");
        fprintf(frep, "------------------------------------------------------------\n");
        int r_idx = 1;
        for (int i = 0; i < NUM_KEYWORDS; i++) {
            if (TABLA_KEYWORDS[i].conteo > 0) {
                fprintf(frep, "%-4d %-15s %-20s %-12d\n",
                        r_idx++, TABLA_KEYWORDS[i].en, TABLA_KEYWORDS[i].es, TABLA_KEYWORDS[i].conteo);
            }
        }
        fclose(frep);
        printf("[OK] Reporte guardado/sobreescrito en: '%s'\n", ruta_reporte);
    }

    /* Liberación de memoria dinámica */
    free(codigo);
    free(traducido);
    return 0;
}

