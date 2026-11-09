#include <stdio.h>

// funcion de prueba con palabras reservadas
int main() {
    int contador = 0;
    double promedio = 15.5;
    const char letra = 'a';

    for (int i = 0; i < 5; i++) {
        contador += i;
        if (contador > 4) {
            break;
        } else {
            continue;
        }
    }

    while (contador > 0) {
        contador--;
    }

    printf("int y return dentro de comillas no se traducen: %d\n", contador);
    return 0;
}