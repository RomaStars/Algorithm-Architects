#include <stdio.h>
#include <stdlib.h>
#include "../include/c_translator.h"

int main(void) {
    printf("===================================================\n");
    printf("  UNEG - LENGUAJES Y COMPILADORES (2026-II)\n");
    printf("  Prueba Diagnostica: Ejercicio 3 (Traductor de C)\n");
    printf("===================================================\n\n");

    const char *sample_file = "codigo_prueba.c";
    const char *output_file = "resultados_ejercicio3.txt";

    // 1. Crear un archivo de prueba C dinamico
    FILE *f_sample = fopen(sample_file, "w");
    if (f_sample) {
        fputs("// Programa de prueba en C\n", f_sample);
        fputs("#include <stdio.h>\n\n", f_sample);
        fputs("int main(void) {\n", f_sample);
        fputs("    int contador = 0;\n", f_sample);
        fputs("    float suma = 0.0;\n", f_sample);
        fputs("    for (int i = 0; i < 10; i++) {\n", f_sample);
        fputs("        if (i % 2 == 0) {\n", f_sample);
        fputs("            contador++;\n", f_sample);
        fputs("        } else {\n", f_sample);
        fputs("            continue;\n", f_sample);
        fputs("        }\n", f_sample);
        fputs("    }\n", f_sample);
        fputs("    while (contador > 0) {\n", f_sample);
        fputs("        contador--;\n", f_sample);
        fputs("        break;\n", f_sample);
        fputs("    }\n", f_sample);
        fputs("    return 0;\n", f_sample);
        fputs("}\n", f_sample);
        fclose(f_sample);
    }

    // 2. Cargar en memoria dinámica el código C
    printf("--- CARGANDO CODIGO C EN MEMORIA DINAMICA ---\n");
    char *code_in_memory = load_file_to_memory(sample_file);

    if (code_in_memory != NULL) {
        printf("\n--- CODIGO TRADUCIDO AL ESPANOL ---\n\n");
        
        // 3. Traducir las palabras reservadas a español y exportar a .txt
        translate_c_keywords(code_in_memory, output_file);

        // Liberar la memoria dinámica asignada
        free(code_in_memory);
    }

    return 0;
}