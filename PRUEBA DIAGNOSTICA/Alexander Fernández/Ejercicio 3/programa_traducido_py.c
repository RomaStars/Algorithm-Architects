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

estructura Persona {
    caracter nombre[50];
    entero edad;
    flotante salario;
};

vacio mostrar_saludo(vacio) {
    // La palabra 'char' e 'int' dentro del texto literal no deben cambiarse:
    printf("Mensaje: Este texto contiene palabras como if, while, int y return literales.\n");
}

entero main(entero argc, caracter *argv[]) {
    entero contador = 0;
    constante doble pi = 3.1415926535;
    
    mostrar_saludo();

    // Estructuras de control
    si (contador == 0) {
        contador += 5;
    } sino {
        contador -= 1;
    }

    para (entero i = 0; i < 3; i++) {
        mientras (contador < 10) {
            contador++;
            si (contador == 8) {
                interrumpir;
            } sino {
                continuar;
            }
        }
    }

    segun (contador) {
        caso 8:
            printf("El contador alcanzo el valor 8 correctamente.\n");
            interrumpir;
        defecto:
            printf("Valor por defecto.\n");
            interrumpir;
    }

    retornar 0;
}

