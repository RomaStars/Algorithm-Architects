# Ejercicio 1: Validador de Movimientos del Caballo en C

**Universidad Nacional Experimental de Guayana (UNEG)**  
**Vicerrectorado Académico**  
**Coordinación de Ingeniería en Informática**  
**Asignatura:** Lenguajes y Compiladores (Periodo Lectivo 2026-II)  
**Profesor:** Msc. Félix Márquez  

---

## 📋 1. Descripción del Problema

El objetivo fundamental de este ejercicio es implementar un analizador y validador de secuencias de movimientos para un único **caballo de ajedrez** ubicado en un tablero estándar de $8 \times 8$. El tablero se encuentra acotado por las filas $[1, 2, 3, 4, 5, 6, 7, 8]$ y las columnas $[a, b, c, d, e, f, g, h]$.

Dada una posición inicial del caballo ($A_k$), una cantidad de movimientos esperada ($n$) y una cadena de caracteres $C$ que denota la secuencia de saltos (donde cada movimiento inicia con la notación en inglés **"K"** de *Knight*, seguida de la columna y la fila destino, por ejemplo `Kc2`):

1. **Validación Léxica/Sintáctica:** Se comprueba que cada instrucción comience por la letra `'K'` y que la coordenada solicitada se mantenga estrictamente dentro de los límites físicos del tablero.
2. **Validación Semántica (Reglas de Ajedrez):** Se evalúa secuencialmente que cada cambio de casilla represente una trayectoria geométrica legal de caballo en forma de "L".
3. **Criterio de Parada Inmediata:** La secuencia se procesa paso a paso. Al detectar el **primer movimiento incorrecto**, el algoritmo interrumpe la ejecución e informa de forma precisa el número de paso donde se produjo el error o el motivo sintáctico de la falla.
4. **Prueba de Rendimiento (Benchmark) y Reporte Automatizado:** El programa ejecuta la verificación de una traza masiva de $500$ movimientos iterada $10$ veces consecutivas (o configurables) partiendo de `a2`, midiendo el tiempo de procesamiento consumido por el procesador y exportando automáticamente los resultados a un archivo plano `resultados_ejercicio1.txt`.

---

## 🧠 2. Fundamento Teórico y Algorítmico

La solución fue desarrollada en C (estándar C99) estructurada en módulos coherentes y limpios:

### 2.1 Conversión y Decodificación de Coordenadas (`parse_position`)
Las coordenadas algebraicas del ajedrez (como `"a1"` o `"H8"`) se traducen mediante aritmética de caracteres a índices numéricos de matriz bidimensional (rango $0$ a $7$):
* **Columna ($c$):** Se calcula restando la base ASCII `'a'` o `'A'`: $c = \text{pos}[0] - \text{'a'}$.
* **Fila ($r$):** Se obtiene restando el carácter `'1'`: $r = \text{pos}[1] - \text{'1'}$.
* Si el carácter no se encuentra dentro del rango de columnas `['a'-'h']`/`['A'-'H']` o filas `['1'-'8']`, la función retorna `false`.

### 2.2 Geometría del Salto del Caballo (`is_valid_knight_move`)
Un desplazamiento desde la posición $(r_1, c_1)$ hacia $(r_2, c_2)$ es estrictamente legal si la magnitud de los deltas absoluto de fila ($\Delta r$) y columna ($\Delta c$) satisfacen la regla geométrica del salto del caballo:
$$\Delta r = |r_1 - r_2|, \quad \Delta c = |c_1 - c_2|$$
$$(\Delta r = 1 \land \Delta c = 2) \quad \lor \quad (\Delta r = 2 \land \Delta c = 1)$$

### 2.3 Procesamiento de la Secuencia (`validate_sequence`)
* Se genera una copia dinámica de la cadena fuente utilizando `strdup` para evitar alterar el string original.
* Se subdivide la cadena token por token utilizando la función de biblioteca `strtok` delimitada por espacios, tabuladores y saltos de línea.
* Para cada movimiento se verifica:
  * **Error Tipo 1:** Si `token[0] != 'K'` (pieza no válida/ausente).
  * **Error Tipo 2:** Si la coordenada destino no es parseable o está fuera del tablero.
  * **Error Tipo 3:** Si la celda destino no es alcanzable geométricamente desde la casilla actual.
* Si el salto es válido, la posición actual $(r, c)$ se actualiza a la nueva posición destino y el ciclo continúa.

### 2.4 Medición de Tiempo y Exportación (`run_benchmark_and_export`)
* **Medición de Tiempos:** Se emplea la función `clock()` de `<time.h>` para obtener los ticks de CPU consumidos antes y después del bucle repetitivo de pruebas. El tiempo en segundos se obtiene dividiendo entre `CLOCKS_PER_SEC`.
* **Persistencia:** Mediante `fopen`, `fprintf` y `fclose`, el sistema escribe un informe detallado con las métricas de la prueba de rendimiento en `resultados_ejercicio1.txt`.

---

## 🗂️ 3. Estructura de Archivos

El proyecto sigue una arquitectura modular en C compatible con entornos de compilación GCC en Windows y Linux:

```text
EJERCICIO1/
├── Makefile
├── README.md
├── include/
│   └── knight_checker.h
└── src/
    ├── knight_checker.c
    └── main.c
```

### Explicación de los componentes del código:
* **`include/knight_checker.h`**: Contiene las declaraciones de las funciones públicas, constantes globales e inclusión de las bibliotecas del sistema (`<stdbool.h>`, `<stdio.h>`).
* **`src/knight_checker.c`**: Contiene la implementación lógica de `parse_position`, `is_valid_knight_move`, `validate_sequence` y `run_benchmark_and_export`.
* **`src/main.c`**: Punto de entrada del programa. Incluye la constante `BENCHMARK_SEQUENCE` (500 movimientos en la posición `a2`), la función auxiliar `print_result` para imprimir las respuestas de los casos solicitados y la invocación de las funciones del sistema.
* **`Makefile`**: Script de automatización de compilación con soporte directo para la limpieza de binarios (`clean`) y generación de ejecutables.

---

## 🚀 4. Instrucciones de Compilación y Ejecución (Windows)

### Requisitos Previos
* Tener instalado un compilador de C compatible con el estándar C99 (ej. **GCC** mediante MinGW-w64, WinLibs o w64devkit).
* *(Opcional)* Herramienta `make` instalada.

---

### Opción A: Usando `make` (Recomendado)
1. Abre tu terminal de mandos (**PowerShell** o **CMD**) en la carpeta raíz del `EJERCICIO1`.
2. Ejecuta el comando de compilación:
   ```cmd
   make
   ```
3. Ejecuta el programa generado:
   ```powershell
   .\knight_checker.exe
   ```

---

### Opción B: Compilación Manual Directa con GCC
Si prefieres compilar directamente usando la terminal de VS Code o la consola de Windows:

```cmd
gcc -Wall -Wextra -std=c99 -Iinclude src/main.c src/knight_checker.c -o knight_checker.exe
```

Posteriormente, ejecuta el programa indicando la ruta local del archivo:

```powershell
.\knight_checker.exe
```

> **Nota para usuarios de PowerShell:** Es necesario anteponer `.\` o `./` para poder ejecutar un archivo binario ubicado en el directorio actual.

---

## 🧪 5. Casos de Prueba en la Guía

El programa evalúa y muestra por consola los casos de prueba provistos en la guía diagnóstica de la materia:

| $A_k$ | $n$ | Cadena de Movimientos ($C$) | Salida Generada por el Programa |
| :---: | :---: | :--- | :--- |
| **a1** | 4 | `Kc2 Kd4 Kb3 Kc5` | `movimiento CORRECTO.` |
| **a1** | 4 | `Kc2 Kd4 Kb4 Kc5` | `INCORRECTO falla en el movimiento 3.` |
| **a2** | 5 | `Ke4 Kf6 Ke8 Kg7` | `movimiento CORRECTO.` |
| **a2** | 5 | `Kc8 Ke4 Kf6 Ke8 Kg7` | `INCORRECTO falla en el movimiento 1.` |
| **a8** | 2 | `Kb6 Kd7` | `movimiento CORRECTO.` |
| **a8** | 2 | `Kb6 Kb7` | `INCORRECTO falla en el movimiento 2.` |
| **a1** | 10 | `Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kb4` | `movimiento CORRECTO.` |
| **a1** | 10 | `Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4` | `INCORRECTO falla letra Q no pertenece a un caballo.` |
| **a1** | 10 | `Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kh6 Kb4` | `INCORRECTO falla en el movimiento 9.` |

---

## 📊 6. Resultados de Rendimiento

El programa procesa el benchmark de validación masiva sobre una secuencia de **500 movimientos continuos** partiendo de la posición inicial `a2`.

### 6.1 Análisis del Comportamiento en C
Al estar implementado en un lenguaje nativo de bajo nivel, la tokenización, el cálculo algebraico de los deltas absolutos y el avance de estado de la matriz en memoria se ejecutan a una velocidad extremadamente alta (tomando fracciones de microsegundos por iteración).

### 6.2 Reporte Generado Automatizado (`resultados_ejercicio1.txt`)
Al culminar la ejecución, el programa crea o sobrescribe automáticamente el archivo de texto `resultados_ejercicio1.txt` en la raíz de la carpeta con un reporte similar a este:

```text
===================================================
  RESULTADOS DE EJECUCION Y BENCHMARK - EJERCICIO 1
===================================================
Posicion Inicial: a2
Movimientos evaluados por iteracion: 500
Repeticiones del benchmark: 10
Resultado de validacion: CORRECTO
Tiempo total: 0.001000 segundos
Tiempo promedio por ejecucion: 0.00010000 segundos (0.100000 ms)
Estado: Verificacion completada exitosamente.
```