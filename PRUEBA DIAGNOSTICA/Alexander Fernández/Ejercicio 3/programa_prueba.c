/**
 * Programa de prueba en lenguaje C para el analizador y traductor.
 * Incluye palabras reservadas legítimas, comentarios y cadenas de texto
 * para comprobar que el analizador léxico no comete falsos positivos.
 */

#include <stdio.h>
#include <stdlib.h>

// Comentario de una línea: el keyword 'if' o 'while' aquí no debe traducirse.
/* Comentario multilínea:
   int a = 10;
   return 0;
   Tampoco deben alterarse las palabras reservadas dentro de comentarios.
*/

struct Persona {
    char nombre[50];
    int edad;
    float salario;
};

void mostrar_saludo(void) {
    // La palabra 'char' e 'int' dentro del texto literal no deben cambiarse:
    printf("Mensaje: Este texto contiene palabras como if, while, int y return literales.\n");
}

int main(int argc, char *argv[]) {
    int contador = 0;
    const double pi = 3.1415926535;
    
    mostrar_saludo();

    // Estructuras de control
    if (contador == 0) {
        contador += 5;
    } else {
        contador -= 1;
    }

    for (int i = 0; i < 3; i++) {
        while (contador < 10) {
            contador++;
            if (contador == 8) {
                break;
            } else {
                continue;
            }
        }
    }

    switch (contador) {
        case 8:
            printf("El contador alcanzo el valor 8 correctamente.\n");
            break;
        default:
            printf("Valor por defecto.\n");
            break;
    }

    return 0;
}

