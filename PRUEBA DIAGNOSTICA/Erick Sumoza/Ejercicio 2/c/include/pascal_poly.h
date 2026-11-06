#ifndef PASCAL_POLY_H
#define PASCAL_POLY_H

#include <stdio.h>

unsigned long long* generate_pascal_coefficients(int n);
void print_polynomial(int n, const unsigned long long *coeffs);
double evaluate_polynomial_step_by_step(int n, const unsigned long long *coeffs, double x);
void run_benchmark_c(int n, int repetitions, const char *filename);

#endif // PASCAL_POLY_H