/* ============================================================================
 * EJERCICIO 3 - PRUEBA DIAGNÓSTICA
 * Lenguajes y Compiladores - UNEG - Periodo 2026-II
 * ----------------------------------------------------------------------------
 * Se carga un programa escrito en C desde un archivo a un búfer reservado
 * DINÁMICAMENTE (malloc + realloc). Luego se recorre el código con un
 * lexer simple que:
 *
 *   - copia tal cual los comentarios // y /* ... *\/
 *   - copia tal cual las cadenas "..." y caracteres '...' (con escapes)
 *   - copia tal cual las directivas de preprocesador (#...)
 *   - identifica identificadores [A-Za-z_][A-Za-z0-9_]*
 *
 * Cada identificador se busca en una TABLA de palabras reservadas de C.
 * Si coincide:
 *   - se reemplaza por su equivalente en español
 *   - se incrementa su contador de ocurrencias
 *
 * Salidas generadas:
 *   - "resultado_ej3_c.txt"          -> reporte de palabras y conteos
 *   - "programa_traducido_c.txt"     -> programa con las palabras traducidas
 *
 * COMPLEJIDAD: O(L) sobre la longitud L del programa.
 * ==========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ===========================================================================
 * TABLA DE PALABRAS RESERVADAS DE C Y SU EQUIVALENTE EN ESPAÑOL
 * =========================================================================*/
typedef struct {
    const char *ingles;
    const char *espanol;
} Traduccion;

static const Traduccion TABLA[] = {
    {"_Alignas",        "alinear_como"},   {"_Alignof",        "alineacion_de"},
    {"_Atomic",         "atomico"},        {"_Bool",           "booleano"},
    {"_Complex",        "complejo"},       {"_Generic",        "generico"},
    {"_Imaginary",      "imaginario"},     {"_Noreturn",       "sin_retorno"},
    {"_Static_assert",  "asercion_estatica"}, {"_Thread_local", "hilo_local"},
    {"auto",            "automatico"},     {"break",           "romper"},
    {"case",            "caso"},           {"char",            "caracter"},
    {"const",           "constante"},      {"continue",        "continuar"},
    {"default",         "por_defecto"},    {"do",              "hacer"},
    {"double",          "doble"},          {"else",            "sino"},
    {"enum",            "enumeracion"},    {"extern",          "externo"},
    {"float",           "flotante"},       {"for",             "para"},
    {"goto",            "ir_a"},           {"if",              "si"},
    {"inline",          "en_linea"},       {"int",             "entero"},
    {"long",            "largo"},          {"register",        "registro"},
    {"restrict",        "restringido"},    {"return",          "retornar"},
    {"short",           "corto"},          {"signed",          "con_signo"},
    {"sizeof",          "tamano_de"},      {"static",          "estatico"},
    {"struct",          "estructura"},     {"switch",          "segun"},
    {"typedef",         "tipo_def"},       {"union",           "union"},
    {"unsigned",        "sin_signo"},      {"void",            "vacio"},
    {"volatile",        "volatil"},        {"while",           "mientras"}
};

#define NTABLA ((int)(sizeof(TABLA) / sizeof(TABLA[0])))

/* Búsqueda lineal en la tabla. Retorna índice o -1 si no está. */
static int buscar_reservada(const char *palabra, size_t len) {
    for (int i = 0; i < NTABLA; i++) {
        if (strlen(TABLA[i].ingles) == len && strncmp(TABLA[i].ingles, palabra, len) == 0) {
            return i;
        }
    }
    return -1;
}

/* ===========================================================================
 * FUNCIÓN: cargar_archivo_dinamico
 * Lee el archivo completo en un búfer que crece dinámicamente.
 * =========================================================================*/
static char *cargar_archivo_dinamico(const char *ruta, size_t *out_len) {
    FILE *f = fopen(ruta, "rb");
    if (!f) return NULL;

    char  *buf = NULL;
    size_t cap = 0;
    size_t len = 0;
    char   chunk[4096];
    size_t n;

    while ((n = fread(chunk, 1, sizeof(chunk), f)) > 0) {
        if (len + n + 1 > cap) {
            size_t nueva = (cap == 0) ? 4096 : cap;
            while (nueva < len + n + 1) nueva *= 2;
            char *tmp = (char *)realloc(buf, nueva);
            if (!tmp) { free(buf); fclose(f); return NULL; }
            buf = tmp;
            cap = nueva;
        }
        memcpy(buf + len, chunk, n);
        len += n;
    }
    fclose(f);

    if (buf == NULL) {
        buf = (char *)malloc(1);
        if (!buf) return NULL;
    }
    buf[len] = '\0';
    *out_len = len;
    return buf;
}

/* ===========================================================================
 * FUNCIÓN: analizar_y_traducir
 * Lexer que recorre el código y traduce las palabras reservadas.
 * =========================================================================*/
static void analizar_y_traducir(const char *codigo, size_t len, FILE *salida, int conteos[NTABLA]) {
    size_t i = 0;
    while (i < len) {
        char c = codigo[i];

        /* Comentario de línea: // ... hasta \n */
        if (c == '/' && i + 1 < len && codigo[i + 1] == '/') {
            while (i < len && codigo[i] != '\n') { fputc(codigo[i], salida); i++; }
            continue;
        }

        /* Comentario de bloque: /* ... *\/ */
        if (c == '/' && i + 1 < len && codigo[i + 1] == '*') {
            fputc(codigo[i], salida); i++;
            fputc(codigo[i], salida); i++;
            while (i + 1 < len && !(codigo[i] == '*' && codigo[i + 1] == '/')) {
                fputc(codigo[i], salida); i++;
            }
            if (i + 1 < len) {
                fputc(codigo[i], salida); i++;
                fputc(codigo[i], salida); i++;
            }
            continue;
        }

        /* Cadena: "..." con escapes */
        if (c == '"') {
            fputc(codigo[i], salida); i++;
            while (i < len) {
                if (codigo[i] == '\\' && i + 1 < len) {
                    fputc(codigo[i], salida); i++;
                    fputc(codigo[i], salida); i++;
                    continue;
                }
                fputc(codigo[i], salida);
                if (codigo[i] == '"') { i++; break; }
                i++;
            }
            continue;
        }

        /* Carácter: '...' con escapes */
        if (c == '\'') {
            fputc(codigo[i], salida); i++;
            while (i < len) {
                if (codigo[i] == '\\' && i + 1 < len) {
                    fputc(codigo[i], salida); i++;
                    fputc(codigo[i], salida); i++;
                    continue;
                }
                fputc(codigo[i], salida);
                if (codigo[i] == '\'') { i++; break; }
                i++;
            }
            continue;
        }

        /* Directiva de preprocesador: # ... hasta \n */
        if (c == '#') {
            while (i < len && codigo[i] != '\n') { fputc(codigo[i], salida); i++; }
            continue;
        }

        /* Identificador */
        if (isalpha((unsigned char)c) || c == '_') {
            size_t ini = i;
            while (i < len && (isalnum((unsigned char)codigo[i]) || codigo[i] == '_')) i++;
            
            size_t wlen = i - ini;
            int idx = buscar_reservada(codigo + ini, wlen);

            if (idx >= 0) {
                fputs(TABLA[idx].espanol, salida);
                conteos[idx]++;
            } else {
                fwrite(codigo + ini, 1, wlen, salida);
            }
            continue;
        }

        /* Cualquier otro carácter */
        fputc(c, salida);
        i++;
    }
}

/* ===========================================================================
 * FUNCIÓN PRINCIPAL: main
 * =========================================================================*/
int main(void) {
    const char *ENTRADA = "programa_ejemplo.c";
    const char *SALIDA_PROG = "programa_traducido_c.txt";
    const char *SALIDA_REP  = "resultado_ej3_c.txt";

    size_t len = 0;
    char *codigo = cargar_archivo_dinamico(ENTRADA, &len);
    if (!codigo) {
        printf("Error: No se encontro '%s'.\n", ENTRADA);
        return 1;
    }

    int conteos[NTABLA] = {0};

    /* 1. Generar el archivo con el código traducido */
    FILE *fprog = fopen(SALIDA_PROG, "w");
    if (fprog) {
        analizar_y_traducir(codigo, len, fprog, conteos);
        fclose(fprog);
    }

    /* 2. Generar el reporte profesional */
    int total = 0;
    for (int i = 0; i < NTABLA; i++) total += conteos[i];

    FILE *frep = fopen(SALIDA_REP, "w");
    if (frep) {
        fprintf(frep, "UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n");
        fprintf(frep, "PRUEBA DIAGNOSTICA - LENGUAJES Y COMPILADORES\n");
        fprintf(frep, "EJERCICIO 3: ANALIZADOR LEXICO Y TRADUCCION (LENGUAJE C)\n");
        fprintf(frep, "======================================================================\n\n");
        
        fprintf(frep, "REPORTE DE ANALISIS DE PALABRAS RESERVADAS:\n");
        fprintf(frep, "Programa analizado: %s\n", ENTRADA);
        fprintf(frep, "Longitud del codigo: %zu bytes\n", len);
        fprintf(frep, "Total de ocurrencias encontradas: %d\n\n", total);

        fprintf(frep, "DETALLE DE PALABRAS TRADUCIDAS:\n");
        for (int i = 0; i < NTABLA; i++) {
            if (conteos[i] > 0) {
                fprintf(frep, "  - %-12s -> %-15s (%d vez%s)\n", 
                        TABLA[i].ingles, TABLA[i].espanol, conteos[i], (conteos[i] == 1) ? "" : "es");
            }
        }
        fprintf(frep, "\nEVIDENCIA DE TRADUCCION:\n");
        fprintf(frep, "El codigo traducido se ha guardado exitosamente en '%s'.\n", SALIDA_PROG);
        fclose(frep);
    }

    printf("Ejecucion en C finalizada. Revisar '%s' y '%s'.\n", SALIDA_REP, SALIDA_PROG);
    free(codigo);
    return 0;
}