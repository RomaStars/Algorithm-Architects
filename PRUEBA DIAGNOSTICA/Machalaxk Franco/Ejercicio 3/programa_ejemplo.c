#include <stdio.h>
#include <stdlib.h>

#define MAXIMO 100

// Estructura para un Nodo de lista enlazada
typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
} Nodo;

/* 
 * Funcion para crear un nodo en memoria dinamica.
 * Retorna un puntero al nuevo nodo.
 */
Nodo* crear_nodo(int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        return NULL;
    }
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    return nuevo;
}

int main(void) {
    const char* mensaje = "Iniciando prueba de \"lexer\"\n";
    char inicial = 'A';
    unsigned int i = 0;
    Nodo* cabeza = crear_nodo(1);
    
    while (i < MAXIMO) {
        switch(i % 3) {
            case 0:
                cabeza->dato += 1;
                break;
            case 1:
                // Ignorar este caso
                break;
            default:
                cabeza->dato -= 1;
                break;
        }
        i++;
    }
    
    printf("Resultado final: %d\n", cabeza->dato);
    free(cabeza);
    return 0;
}