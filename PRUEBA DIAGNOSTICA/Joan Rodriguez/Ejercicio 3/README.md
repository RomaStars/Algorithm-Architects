# Ejercicio 3: Verificación y Traducción de Palabras Reservadas de C al Español

**Universidad Nacional Experimental de Guayana**  
**Coordinación de Ingeniería en Informática**  
**Lenguajes y Compiladores — Periodo 2026-II**  
**Estudiante:** Joan Rodríguez  
**Profesor:** Msc. Félix Márquez  

---

## 1. Descripción del Problema

Dado un programa fuente escrito en C, el programa debe:

1. **Cargar el archivo `.c` completo** en memoria dinámica.
2. **Identificar todas las palabras reservadas** del estándar C (32 en total), distinguiéndolas de identificadores de usuario, literales de cadena, comentarios y directivas del preprocesador.
3. **Traducir las palabras reservadas** del inglés al español, generando una versión modificada del código fuente.
4. **Reportar un conteo** de cada palabra reservada encontrada y sus apariciones.

*Nota: Se implementó en **C** para demostrar el manejo explícito de memoria dinámica con `malloc`, `realloc`, `calloc` y `free`, alineándose con los objetivos de la prueba diagnóstica sobre gestión de memoria.*

---

## 2. Fundamento Teórico y Algorítmico

### 2.1. Análisis Léxico Simplificado

El programa implementa un **analizador léxico (scanner)** básico que clasifica el texto fuente en categorías:

| Categoría | Tratamiento | Ejemplo |
| :--- | :--- | :--- |
| Comentarios de línea (`//`) | Se copian sin modificar | `// funcion de prueba` |
| Comentarios de bloque (`/* */`) | Se copian sin modificar | `/* comentario */` |
| Literales de cadena (`"..."`) | Se copian sin modificar | `"int y return no se traducen"` |
| Literales de carácter (`'...'`) | Se copian sin modificar | `'a'` |
| Directivas (`#include`, `#define`) | Se copian sin modificar | `#include <stdio.h>` |
| Identificadores / palabras reservadas | Se buscan en el diccionario | `int` → `entero` |
| Otros símbolos y operadores | Se copian sin modificar | `{`, `+=`, `;` |

### 2.2. Diccionario de las 32 Palabras Reservadas de C

El programa mantiene un arreglo estático de estructuras `PalabraReservada` con los pares inglés-español:

| Inglés | Español | | Inglés | Español |
|:---|:---|:---|:---|:---|
| `auto` | `automatico` | | `int` | `entero` |
| `break` | `romper` | | `long` | `largo` |
| `case` | `caso` | | `register` | `registro` |
| `char` | `caracter` | | `return` | `retornar` |
| `const` | `constante` | | `short` | `corto` |
| `continue` | `continuar` | | `signed` | `con_signo` |
| `default` | `predeterminado` | | `sizeof` | `tamano_de` |
| `do` | `hacer` | | `static` | `estatico` |
| `double` | `doble` | | `struct` | `estructura` |
| `else` | `sino` | | `switch` | `segun` |
| `enum` | `enumeracion` | | `typedef` | `definir_tipo` |
| `extern` | `externo` | | `union` | `union` |
| `float` | `flotante` | | `unsigned` | `sin_signo` |
| `for` | `para` | | `void` | `vacio` |
| `goto` | `ir_a` | | `volatile` | `volatil` |
| `if` | `si` | | `while` | `mientras` |

### 2.3. Gestión de Memoria Dinámica

El programa utiliza cuatro funciones de gestión de memoria:

| Función | Uso en el programa |
| :--- | :--- |
| `malloc()` | Cargar archivo fuente en buffer, reservar buffer de salida traducido, extraer tokens temporales |
| `realloc()` | Redimensionar el buffer de salida cuando crece más allá de la capacidad actual |
| `calloc()` | Reservar e inicializar a cero el arreglo de conteo de apariciones |
| `free()` | Liberar código original, código traducido, tokens temporales y arreglo de conteo |

### 2.4. Complejidad Computacional

- **Complejidad Temporal:** $O(m \times k)$, donde $m$ es la cantidad de tokens en el código fuente y $k = 32$ es el tamaño del diccionario (búsqueda lineal). En la práctica, $k$ es constante, por lo que es efectivamente $O(m)$.
- **Complejidad Espacial:** $O(n)$, donde $n$ es el tamaño del archivo fuente. Se mantiene el original y la traducción simultáneamente en memoria.

---

## 3. Estructura de Archivos

| Archivo | Descripción |
| :--- | :--- |
| `ejercicio3.c` | Implementación del analizador léxico y traductor en C. |
| `muestra.c` | Programa C de ejemplo usado como entrada para la traducción. |
| `resultado_ej3.txt` | Reporte con la salida completa del programa. |
| `README.md` | Documentación técnica y académica del ejercicio. |

---

## 4. Instrucciones de Ejecución

### Compilar y ejecutar:
```bash
gcc ejercicio3.c -o ejercicio3
./ejercicio3
```

> **Nota:** El archivo `muestra.c` debe estar en el mismo directorio que el ejecutable.

---

## 5. Resultados de la Traducción

### 5.1. Palabras Reservadas Detectadas

El programa analizó `muestra.c` y encontró **11 palabras reservadas distintas** con un total de **13 apariciones**:

| Palabra Reservada | Traducción | Apariciones |
|:---:|:---:|:---:|
| `break` | `romper` | 1 |
| `char` | `caracter` | 1 |
| `const` | `constante` | 1 |
| `continue` | `continuar` | 1 |
| `double` | `doble` | 1 |
| `else` | `sino` | 1 |
| `for` | `para` | 1 |
| `if` | `si` | 1 |
| `int` | `entero` | 3 |
| `return` | `retornar` | 1 |
| `while` | `mientras` | 1 |
| **Total** | | **13** |

### 5.2. Código Original vs. Código Traducido

**Fragmento original:**
```c
int main() {
    int contador = 0;
    double promedio = 15.5;
    const char letra = 'a';

    for (int i = 0; i < 5; i++) {
        if (contador > 4) {
            break;
        } else {
            continue;
        }
    }

    while (contador > 0) {
        contador--;
    }

    return 0;
}
```

**Fragmento traducido:**
```c
entero main() {
    entero contador = 0;
    doble promedio = 15.5;
    constante caracter letra = 'a';

    para (entero i = 0; i < 5; i++) {
        si (contador > 4) {
            romper;
        } sino {
            continuar;
        }
    }

    mientras (contador > 0) {
        contador--;
    }

    retornar 0;
}
```

### 5.3. Correcta Exclusión de Falsos Positivos

El programa correctamente **no traduce** palabras reservadas dentro de cadenas literales:
```c
printf("int y return dentro de comillas no se traducen: %d\n", contador);
```
Esta línea permanece intacta en la salida, demostrando que el analizador léxico distingue correctamente entre tokens del lenguaje y contenido de cadenas.

---

## 6. Análisis de la Gestión de Memoria

| Etapa | Operación | Detalle |
| :--- | :--- | :--- |
| Carga del archivo | `malloc(tam + 1)` | Buffer del tamaño exacto del archivo + null terminator |
| Buffer de salida | `malloc(cap)` con `realloc()` dinámico | Capacidad inicial de $2n + 128$; se duplica si es insuficiente |
| Arreglo de conteo | `calloc(32, sizeof(int))` | 32 enteros inicializados a 0 |
| Tokens temporales | `malloc(tam_pal + 1)` + `free(token)` | Se reserva y libera por cada identificador encontrado |
| Liberación final | 3 llamadas a `free()` | `codigo_original`, `codigo_traducido`, `conteo` |

No se producen fugas de memoria: toda la memoria dinámica reservada es liberada explícitamente antes de que el programa termine.
