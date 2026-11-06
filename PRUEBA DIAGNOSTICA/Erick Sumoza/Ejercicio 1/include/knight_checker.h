#ifndef KNIGHT_CHECKER_H
#define KNIGHT_CHECKER_H

#include <stdbool.h>
#include <stdio.h>

// Convierte notación de ajedrez ("a1") a coordenadas de matriz (0 a 7)
bool parse_position(const char *pos, int *col, int *row);

// Verifica si un movimiento de un punto (r1, c1) a (r2, c2) es válido para un caballo
bool is_valid_knight_move(int r1, int c1, int r2, int c2);

// Procesa la cadena de movimientos y determina su validez
int validate_sequence(const char *start_pos, int n, const char *sequence_str, int *error_type);

// Ejecuta el benchmark, imprime en consola y escribe los resultados en un archivo .txt
void run_benchmark_and_export(const char *start_pos, const char *sequence_str, int repetitions, const char *filename);

#endif // KNIGHT_CHECKER_H