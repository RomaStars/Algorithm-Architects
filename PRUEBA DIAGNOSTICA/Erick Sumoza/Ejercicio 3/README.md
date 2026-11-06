# Ejercicio 3: Traductor de Palabras Reservadas de C a Español

**Universidad Nacional Experimental de Guayana (UNEG)**  
**Vicerrectorado Académico**  
**Coordinación de Ingeniería en Informática**  
**Asignatura:** Lenguajes y Compiladores (Periodo Lectivo: 2026-II)  
**Profesor:** Msc. Félix Márquez  

---

## 📋 1. Descripción del Problema

El objetivo fundamental de este ejercicio es implementar un analizador y traductor léxico en **Lenguaje C (ANSI C89/C99)** que procese archivos de código fuente escritos en C, los cargue dinámicamente en memoria y realice la traducción de sus palabras reservadas al idioma español.

### Requerimientos Funcionales:
1. **Carga Dinámica en Memoria:** Leer el archivo fuente completo desde el sistema de archivos asignando memoria de forma dinámica en tiempo de ejecución.
2. **Reconocimiento Léxico de Palabras Reservadas:** Identificar las palabras clave estándar del lenguaje C (`int`, `float`, `for`, `if`, `while`, `return`, `break`, `continue`, etc.).
3. **Traducción Contextual:** Reemplazar las palabras reservadas por sus equivalentes predefinidos en español (por ejemplo, `int` $\rightarrow$ `entero`, `while` $\rightarrow$ `mientras`).
4. **Preservación de Sintaxis y Literalidad:** Garantizar que las constantes de texto entre comillas (`"..."`), los comentarios de una línea (`//...`), los comentarios multilínea (`/*...*/`), delimitadores, operadores e identificadores definidos por el usuario no se modifiquen.
5. **Generación de Salida:** Mostrar el código traducido en la consola estándar y exportar el resultado final a un archivo plano (`resultados_ejercicio3.txt`).

---

## 🧠 2. Fundamento Teórico y Algorítmico

El desarrollo del traductor se basa en los principios de análisis léxico y gestión dinámica de recursos en bajo nivel:

### A. Carga Dinámica de Archivos en Memoria (`load_file_to_memory`)
Para procesar archivos de cualquier tamaño sin reservar arreglos estáticos de tamaño fijo, se utiliza la manipulación de punteros de archivo:
* Mediante `fseek(file, 0, SEEK_END)` y `ftell(file)` se determina el tamaño exacto en bytes del archivo.
* Se efectúa una asignación de memoria dinámica utilizando `malloc(length + 1)`.
* Se efectúa la lectura completa en el buffer con `fread` y se añade el carácter nulo de terminación `'\0'`.

### B. Mapeo de Diccionario Léxico (`KEYWORD_MAP`)
Se define una estructura llamada `KeywordMapping` que vincula la palabra clave en inglés con su traducción en español:

$$\text{KeywordMapping} = \{ \text{keyword: const char*}, \text{spanish: const char*} \}$$

La búsqueda se implementa a través de la función `find_spanish_translation` utilizando comparaciones exactas de cadenas (`strcmp`).

### C. Autómata de Tokenización y Filtrado (`translate_c_keywords`)
El algoritmo recorre la secuencia de caracteres en memoria mediante un ciclo `while` comprobando diferentes estados para preservar la estructura original del código:

1. **Comentarios de una línea (`//`):** Avanza y copia directamente todos los caracteres hasta hallar un salto de línea `\n`.
2. **Comentarios multilínea (`/* ... */`):** Avanza y copia los caracteres hasta encontrar el delimitador de cierre `*/`.
3. **Cadenas de texto literales (`"`):** Preserva el contenido textual omitiendo la traducción incluso si la cadena contiene una palabra reservada (ejemplo: `"int total"` se mantiene intacto). Soporta secuencias de escape (`\"`).
4. **Identificadores y Palabras Reservadas:** Al detectar un carácter alfabético o guión bajo (`isalpha(c) || c == '_'`), extrae la palabra completa mediante `isalnum`. Si la palabra coincide con la tabla de palabras reservadas, escribe la traducción; de lo contrario, conserva el identificador original.
5. **Delimitadores y Operadores:** Símbolos como `{`, `}`, `(`, `)`, `;`, `+`, `=`, etc., se copian directamente al flujo de salida.

---

## 🗂️ 3. Estructura de Archivos

El proyecto sigue una estructura limpia y modularizada:

```text
EJERCICIO3/
├── Makefile
├── README.md
├── include/
│   └── c_translator.h
└── src/
    ├── c_translator.c
    └── main.c
```

### Explicación de los Módulos:
* **`include/c_translator.h`**: Contiene la definición del tipo de dato `KeywordMapping` y la declaración de prototipos de funciones.
* **`src/c_translator.c`**: Contiene la tabla con las 32 palabras reservadas estándar, la implementación del motor de carga en memoria (`load_file_to_memory`) y la lógica del traductor léxico (`translate_c_keywords`).
* **`src/main.c`**: Programa principal que crea un archivo C de prueba en tiempo de ejecución (`codigo_prueba.c`), invoca la carga en memoria dinámica, ejecuta la traducción y libera la memoria asignada (`free`).
* **`Makefile`**: Script automatizador para compilación limpia y enlazado con GCC en Windows.

---

## 🚀 4. Instrucciones de Compilación y Ejecución (Windows)

### Requisitos Previos:
* Tener instalado un compilador GCC compatible con C99 (vía MinGW-w64, WinLibs o MSYS2).

### Opción A: Compilación y Ejecución con `make` (Recomendado)
Abre PowerShell o la consola interactiva en la carpeta `EJERCICIO3/` y ejecuta:

```cmd
make
.\translator.exe
```

### Opción B: Compilación Manual Directa con GCC
Si prefieres ejecutar el comando directamente en la terminal:

```powershell
gcc -Wall -Wextra -std=c99 -Iinclude src/main.c src/c_translator.c -o translator.exe
.\translator.exe
```

*Nota: Al finalizar la ejecución, se generará el archivo traducido `resultados_ejercicio3.txt`.*

---

## 🧪 5. Casos de Prueba en la Guía

El archivo `src/main.c` genera y procesa automáticamente una estructura de código de prueba representativa de C:

### Código de Entrada (`codigo_prueba.c`):
```c
// Programa de prueba en C
#include <stdio.h>

int main(void) {
    int contador = 0;
    float suma = 0.0;
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            contador++;
        } else {
            continue;
        }
    }
    while (contador > 0) {
        contador--;
        break;
    }
    return 0;
}
```

### Código Traducido Resultante (`resultados_ejercicio3.txt`):
```c
// Programa de prueba en C
#include <stdio.h>

entero main(vacio) {
    entero contador = 0;
    flotante suma = 0.0;
    para (entero i = 0; i < 10; i++) {
        si (i % 2 == 0) {
            contador++;
        } sino {
            continuar;
        }
    }
    mientras (contador > 0) {
        contador--;
        romper;
    }
    retornar 0;
}
```

---

## 📊 6. Resultados de Rendimiento

1. **Eficiencia del Análisis Léxico:**  
   El algoritmo de tokenización opera en complejidad temporal lineal $\mathcal{O}(N)$, donde $N$ representa el número total de caracteres del código fuente. Dado que realiza una lectura de un solo paso (*single-pass scanner*), el tiempo de procesamiento para archivos de código estándar es de **fracciones de milisegundo**.

2. **Gestión Dinámica de Memoria:**  
   La reserva explícita de memoria mediante `malloc` permite procesar códigos fuente de cualquier longitud sin saturar la pila (*stack*). Al término del procesamiento, toda la memoria asignada en el *heap* se libera adecuadamente mediante `free(code_in_memory)`, garantizando cero fugas de memoria (*memory leaks*).

3. **Verificación de Exportación:**  
   El sistema escribe simultáneamente la salida traducida a la consola y al archivo de salida `resultados_ejercicio3.txt`, confirmando la correcta persistencia de datos.