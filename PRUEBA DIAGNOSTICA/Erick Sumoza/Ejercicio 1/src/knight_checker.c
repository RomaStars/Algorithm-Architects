#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/knight_checker.h"

bool parse_position(const char *pos, int *col, int *row) {
    if (!pos || strlen(pos) < 2) return false;
    
    char c = pos[0];
    char r = pos[1];
    
    if (c >= 'a' && c <= 'h') *col = c - 'a';
    else if (c >= 'A' && c <= 'H') *col = c - 'A';
    else return false;
    
    if (r >= '1' && r <= '8') *row = r - '1';
    else return false;
    
    return true;
}

bool is_valid_knight_move(int r1, int c1, int r2, int c2) {
    int dr = abs(r1 - r2);
    int dc = abs(c1 - c2);
    return (dr == 1 && dc == 2) || (dr == 2 && dc == 1);
}

int validate_sequence(const char *start_pos, int n, const char *sequence_str, int *error_type) {
    *error_type = 0;
    int cur_col, cur_row;
    
    if (!parse_position(start_pos, &cur_col, &cur_row)) {
        *error_type = 2;
        return 0; 
    }

    char *seq_copy = strdup(sequence_str);
    if (!seq_copy) return -1;

    char *token = strtok(seq_copy, " \t\r\n");
    int move_count = 0;
    int failed_move = 0;

    while (token != NULL && move_count < n) {
        move_count++;

        if (token[0] != 'K') {
            *error_type = 1; 
            failed_move = move_count;
            break;
        }

        int next_col, next_row;
        if (!parse_position(token + 1, &next_col, &next_row)) {
            *error_type = 2; 
            failed_move = move_count;
            break;
        }

        if (!is_valid_knight_move(cur_row, cur_col, next_row, next_col)) {
            *error_type = 3; 
            failed_move = move_count;
            break;
        }

        cur_col = next_col;
        cur_row = next_row;

        token = strtok(NULL, " \t\r\n");
    }

    free(seq_copy);
    return failed_move;
}

void run_benchmark_and_export(const char *start_pos, const char *sequence_str, int repetitions, const char *filename) {
    printf("\n=== EJECUTANDO BENCHMARK DE TIEMPO (%d iteraciones) ===\n", repetitions);
    
    clock_t start_time = clock();

    int error_type = 0;
    int result = 0;
    for (int i = 0; i < repetitions; i++) {
        result = validate_sequence(start_pos, 500, sequence_str, &error_type);
    }

    clock_t end_time = clock();
    double cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    double avg_ms = (cpu_time_used / repetitions) * 1000.0;

    if (result == 0) {
        printf("Resultado del Benchmark: Todos los 500 movimientos son CORRECTOS.\n");
    } else {
        printf("Resultado del Benchmark: Falla detectada en el movimiento %d.\n", result);
    }
    printf("Tiempo total invertido (%d ejecuciones): %.6f segundos.\n", repetitions, cpu_time_used);
    printf("Tiempo promedio por verificacion: %.6f milisegundos.\n", avg_ms);

    // Generar y escribir el archivo .txt con los resultados
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: No se pudo crear el archivo %s\n", filename);
        return;
    }

    fprintf(file, "===================================================\n");
    fprintf(file, "  RESULTADOS DE EJECUCION Y BENCHMARK - EJERCICIO 1\n");
    fprintf(file, "===================================================\n");
    fprintf(file, "Posicion Inicial: %s\n", start_pos);
    fprintf(file, "Movimientos evaluados por iteracion: 500\n");
    fprintf(file, "Repeticiones del benchmark: %d\n", repetitions);
    fprintf(file, "Resultado de validacion: %s\n", (result == 0) ? "CORRECTO" : "INCORRECTO");
    fprintf(file, "Tiempo total: %.6f segundos\n", cpu_time_used);
    fprintf(file, "Tiempo promedio por ejecucion: %.8f segundos (%.6f ms)\n", (cpu_time_used / repetitions), avg_ms);
    fprintf(file, "Estado: Verificacion completada exitosamente.\n");

    fclose(file);
    printf("Resultados guardados exitosamente en '%s'\n", filename);
}