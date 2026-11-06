#include "../include/c_translator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Tabla con las 32 palabras reservadas estándar de C (ANSI C89/C99) y su traducción
static const KeywordMapping KEYWORD_MAP[] = {
    {"auto", "auto_local"},
    {"break", "romper"},
    {"case", "caso"},
    {"char", "caracter"},
    {"const", "constante"},
    {"continue", "continuar"},
    {"default", "defecto"},
    {"do", "hacer"},
    {"double", "doble"},
    {"else", "sino"},
    {"enum", "enumeracion"},
    {"extern", "externo"},
    {"float", "flotante"},
    {"for", "para"},
    {"goto", "ir_a"},
    {"if", "si"},
    {"inline", "en_linea"},
    {"int", "entero"},
    {"long", "largo"},
    {"register", "registro"},
    {"restrict", "restringido"},
    {"return", "retornar"},
    {"short", "corto"},
    {"signed", "con_signo"},
    {"sizeof", "tamano_de"},
    {"static", "estatico"},
    {"struct", "estructura"},
    {"switch", "segun"},
    {"typedef", "definir_tipo"},
    {"union", "union"},
    {"unsigned", "sin_signo"},
    {"void", "vacio"},
    {"volatile", "volatil"},
    {"while", "mientras"}
};

static const int NUM_KEYWORDS = sizeof(KEYWORD_MAP) / sizeof(KEYWORD_MAP[0]);

// Busca si una cadena es una palabra reservada de C
static const char* find_spanish_translation(const char *word) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(word, KEYWORD_MAP[i].keyword) == 0) {
            return KEYWORD_MAP[i].spanish;
        }
    }
    return NULL;
}

// Carga el contenido completo de un archivo en un buffer asignado dinámicamente
char* load_file_to_memory(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error al abrir el archivo de entrada");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Asignación dinámica de memoria para el buffer
    char *buffer = (char *)malloc(length + 1);
    if (!buffer) {
        fclose(file);
        fprintf(stderr, "Error: Memoria insuficiente para cargar el archivo.\n");
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

// Traduce el código C identificando tokens y preservando cadenas/comentarios
void translate_c_keywords(const char *source_code, const char *output_filename) {
    FILE *out = stdout;
    FILE *file_out = NULL;

    if (output_filename != NULL) {
        file_out = fopen(output_filename, "w");
        if (!file_out) {
            perror("Error al crear el archivo de salida");
        }
    }

    int i = 0;
    int len = (int)strlen(source_code);

    while (i < len) {
        // Preservar comentarios de una línea (//...)
        if (source_code[i] == '/' && source_code[i + 1] == '/') {
            while (i < len && source_code[i] != '\n') {
                fputc(source_code[i], stdout);
                if (file_out) fputc(source_code[i], file_out);
                i++;
            }
            continue;
        }

        // Preservar comentarios multilínea (/*...*/)
        if (source_code[i] == '/' && source_code[i + 1] == '*') {
            fputc(source_code[i], stdout);
            if (file_out) fputc(source_code[i], file_out);
            i++;
            fputc(source_code[i], stdout);
            if (file_out) fputc(source_code[i], file_out);
            i++;
            while (i < len - 1 && !(source_code[i] == '*' && source_code[i + 1] == '/')) {
                fputc(source_code[i], stdout);
                if (file_out) fputc(source_code[i], file_out);
                i++;
            }
            if (i < len - 1) {
                fputc(source_code[i], stdout);
                if (file_out) fputc(source_code[i], file_out);
                i++;
                fputc(source_code[i], stdout);
                if (file_out) fputc(source_code[i], file_out);
                i++;
            }
            continue;
        }

        // Preservar constantes de texto entre comillas ("...")
        if (source_code[i] == '"') {
            fputc(source_code[i], stdout);
            if (file_out) fputc(source_code[i], file_out);
            i++;
            while (i < len && source_code[i] != '"') {
                if (source_code[i] == '\\' && i + 1 < len) {
                    fputc(source_code[i], stdout);
                    if (file_out) fputc(source_code[i], file_out);
                    i++;
                }
                fputc(source_code[i], stdout);
                if (file_out) fputc(source_code[i], file_out);
                i++;
            }
            if (i < len) {
                fputc(source_code[i], stdout);
                if (file_out) fputc(source_code[i], file_out);
                i++;
            }
            continue;
        }

        // Procesar identificadores y palabras reservadas
        if (isalpha(source_code[i]) || source_code[i] == '_') {
            char word[128];
            int w_len = 0;

            while (i < len && (isalnum(source_code[i]) || source_code[i] == '_')) {
                if (w_len < 127) {
                    word[w_len++] = source_code[i];
                }
                i++;
            }
            word[w_len] = '\0';

            const char *translation = find_spanish_translation(word);
            if (translation) {
                fputs(translation, stdout);
                if (file_out) fputs(translation, file_out);
            } else {
                fputs(word, stdout);
                if (file_out) fputs(word, file_out);
            }
            continue;
        }

        // Cualquier otro carácter (operadores, delimitadores, espacios, saltos de línea)
        fputc(source_code[i], stdout);
        if (file_out) fputc(source_code[i], file_out);
        i++;
    }

    if (file_out) {
        fclose(file_out);
        printf("\n\n[INFO] La traduccion se ha guardado exitosamente en: %s\n", output_filename);
    }
}