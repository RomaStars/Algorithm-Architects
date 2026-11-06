#ifndef C_TRANSLATOR_H
#define C_TRANSLATOR_H

#include <stdio.h>
#include <stdbool.h>

// Estructura para mapear palabras reservadas de C a español
typedef struct {
    const char *keyword;
    const char *spanish;
} KeywordMapping;

// Carga dinámicamente un archivo de código C en memoria
char* load_file_to_memory(const char *filename);

// Analiza el código cargado en memoria, traduce las palabras reservadas y escribe en archivo/consola
void translate_c_keywords(const char *source_code, const char *output_filename);

#endif // C_TRANSLATOR_H