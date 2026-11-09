#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// par de palabra reservada en c y su equivalente en espanol
typedef struct {
    const char *ingles;
    const char *espanol;
} PalabraReservada;

// diccionario con las 32 palabras reservadas estandar de c
const PalabraReservada diccionario[] = {
    {"auto", "automatico"},     {"break", "romper"},
    {"case", "caso"},           {"char", "caracter"},
    {"const", "constante"},     {"continue", "continuar"},
    {"default", "predeterminado"},{"do", "hacer"},
    {"double", "doble"},        {"else", "sino"},
    {"enum", "enumeracion"},    {"extern", "externo"},
    {"float", "flotante"},      {"for", "para"},
    {"goto", "ir_a"},           {"if", "si"},
    {"int", "entero"},          {"long", "largo"},
    {"register", "registro"},   {"return", "retornar"},
    {"short", "corto"},         {"signed", "con_signo"},
    {"sizeof", "tamano_de"},    {"static", "estatico"},
    {"struct", "estructura"},   {"switch", "segun"},
    {"typedef", "definir_tipo"},{"union", "union"},
    {"unsigned", "sin_signo"},  {"void", "vacio"},
    {"volatile", "volatil"},    {"while", "mientras"}
};

const int TOTAL_RESERVADAS = 32;

// carga un archivo .c completo en memoria dinamica
char* cargar_programa(const char *ruta) {
    FILE *f = fopen(ruta, "rb");
    if (f == NULL) return NULL;

    // obtener tamano exacto del archivo
    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    rewind(f);

    // reservar memoria dinamica para el codigo fuente
    char *buffer = (char*)malloc((tam + 1) * sizeof(char));
    if (buffer == NULL) {
        fclose(f);
        return NULL;
    }

    size_t leidos = fread(buffer, 1, tam, f);
    buffer[leidos] = '\0';
    fclose(f);
    return buffer;
}

// busca si un identificador es palabra reservada y devuelve su indice
int buscar_reservada(const char *palabra) {
    for (int i = 0; i < TOTAL_RESERVADAS; i++) {
        if (strcmp(palabra, diccionario[i].ingles) == 0) {
            return i;
        }
    }
    return -1;
}

// agrega texto a un buffer dinamico redimensionando si hace falta
void agregar_texto(char **dest, size_t *len, size_t *cap, const char *txt, size_t n) {
    if (*len + n + 1 >= *cap) {
        *cap = (*cap + n + 1) * 2;
        *dest = (char*)realloc(*dest, *cap);
    }
    memcpy(*dest + *len, txt, n);
    *len += n;
    (*dest)[*len] = '\0';
}

// analiza el codigo en memoria dinamica y traduce las palabras reservadas
char* verificar_y_traducir(const char *codigo, int *conteo) {
    size_t cap = strlen(codigo) * 2 + 128;
    size_t len = 0;
    char *traducido = (char*)malloc(cap * sizeof(char));
    if (traducido == NULL) return NULL;
    traducido[0] = '\0';

    int i = 0;
    while (codigo[i] != '\0') {
        // ignorar comentarios de una linea //
        if (codigo[i] == '/' && codigo[i + 1] == '/') {
            int ini = i;
            while (codigo[i] != '\0' && codigo[i] != '\n') i++;
            agregar_texto(&traducido, &len, &cap, &codigo[ini], i - ini);
        }
        // ignorar comentarios multilinea /* */
        else if (codigo[i] == '/' && codigo[i + 1] == '*') {
            int ini = i;
            i += 2;
            while (codigo[i] != '\0' && !(codigo[i] == '*' && codigo[i + 1] == '/')) i++;
            if (codigo[i] != '\0') i += 2;
            agregar_texto(&traducido, &len, &cap, &codigo[ini], i - ini);
        }
        // ignorar cadenas literales "..." y caracteres '...'
        else if (codigo[i] == '"' || codigo[i] == '\'') {
            char delim = codigo[i];
            int ini = i++;
            while (codigo[i] != '\0' && codigo[i] != delim) {
                if (codigo[i] == '\\' && codigo[i + 1] != '\0') i++;
                i++;
            }
            if (codigo[i] == delim) i++;
            agregar_texto(&traducido, &len, &cap, &codigo[ini], i - ini);
        }
        // ignorar directivas de preprocesador (#include, #define)
        else if (codigo[i] == '#') {
            int ini = i;
            while (codigo[i] != '\0' && codigo[i] != '\n') i++;
            agregar_texto(&traducido, &len, &cap, &codigo[ini], i - ini);
        }
        // procesar identificadores o palabras reservadas
        else if (isalpha((unsigned char)codigo[i]) || codigo[i] == '_') {
            int ini = i;
            while (isalnum((unsigned char)codigo[i]) || codigo[i] == '_') i++;
            int tam_pal = i - ini;

            // extraer token en memoria dinamica temporal
            char *token = (char*)malloc((tam_pal + 1) * sizeof(char));
            memcpy(token, &codigo[ini], tam_pal);
            token[tam_pal] = '\0';

            int idx = buscar_reservada(token);
            if (idx != -1) {
                conteo[idx]++;
                const char *esp = diccionario[idx].espanol;
                agregar_texto(&traducido, &len, &cap, esp, strlen(esp));
            } else {
                agregar_texto(&traducido, &len, &cap, token, tam_pal);
            }
            free(token);
        }
        // copiar cualquier otro simbolo u operador
        else {
            agregar_texto(&traducido, &len, &cap, &codigo[i], 1);
            i++;
        }
    }

    return traducido;
}

int main() {
    const char *archivo_entrada = "muestra.c";

    // 1. cargar el programa c en memoria dinamica
    char *codigo_original = cargar_programa(archivo_entrada);
    if (codigo_original == NULL) {
        printf("error: no se pudo abrir '%s'. asegurate de crearlo en la misma carpeta.\n", archivo_entrada);
        return 1;
    }

    // reservar arreglo dinamico para contar apariciones de cada palabra
    int *conteo = (int*)calloc(TOTAL_RESERVADAS, sizeof(int));

    // 2. verificar palabras reservadas y generar traduccion en memoria dinamica
    char *codigo_traducido = verificar_y_traducir(codigo_original, conteo);

    printf("=== codigo original cargado en memoria dinamica (%s) ===\n", archivo_entrada);
    printf("%s\n", codigo_original);

    printf("=== palabras reservadas encontradas y su traduccion ===\n");
    int total_halladas = 0;
    for (int i = 0; i < TOTAL_RESERVADAS; i++) {
        if (conteo[i] > 0) {
            printf("  %-10s -> %-15s (%d apariciones)\n",
                   diccionario[i].ingles, diccionario[i].espanol, conteo[i]);
            total_halladas += conteo[i];
        }
    }
    printf("total de palabras reservadas traducidas: %d\n\n", total_halladas);

    printf("=== codigo con palabras reservadas traducidas al espanol ===\n");
    printf("%s\n", codigo_traducido);

    // 3. liberar toda la memoria dinamica utilizada
    free(codigo_original);
    free(codigo_traducido);
    free(conteo);

    return 0;
}