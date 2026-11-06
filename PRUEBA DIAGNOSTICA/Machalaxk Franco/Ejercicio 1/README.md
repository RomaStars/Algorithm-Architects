# Ejercicio 1: Verificación de Movimientos de Caballo en Ajedrez

**Universidad Nacional Experimental de Guayana**  
**Coordinación de Ingeniería en Informática**  
**Lenguajes y Compiladores — Periodo 2026-II**  
**Estudiante:** Mchalaxk Franco  
**Profesor:** Msc. Félix Márquez  

---

## 1. Descripción del Problema
Dado un tablero de ajedrez estándar de $8 \times 8$ denotado por:
- **Columnas:** `['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']`
- **Filas:** `['1', '2', '3', '4', '5', '6', '7', '8']`

En el tablero se encuentra un único caballo con posición inicial $A_k$ (por ejemplo, `a1`, `a2`, `a8`). Se recibe una cadena $C$ con $n$ movimientos en notación abreviada (prefijo `K` seguido de la columna y fila destino, ej. `Kc2`).

El programa debe verificar secuencialmente los movimientos e indicar:
1. Si todos son correctos: `"movimiento CORRECTO."`
2. Si un movimiento contiene un identificador que no corresponde al caballo (por ejemplo `Qb4`):  
   `"movimiento INCORRECTO falla letra {letra} no pertenece a un caballo."`
3. Si un movimiento es inválido (fuera del tablero o no cumple el patrón en "L"):  
   `"movimiento INCORRECTO falla en el movimiento {i}."`
4. El análisis se detiene inmediatamente al encontrar el primer fallo (evaluación en cortocircuito).

---

## 2. Fundamento Teórico y Algorítmico

### 2.1. Regla de Movimiento del Caballo
En ajedrez, el caballo se desplaza en forma de "L", lo que equivale matemáticamente a una distancia métrica en el plano discreto de:
$$\Delta x^2 + \Delta y^2 = 5$$

O expresado en diferencias absolutas entre coordenadas:
$$(|\Delta \text{columna}| = 1 \land |\Delta \text{fila}| = 2) \quad \lor \quad (|\Delta \text{columna}| = 2 \land |\Delta \text{fila}| = 1)$$

### 2.2. Gestión de Memoria Dinámica y Nomenclatura
- **En C (`ejercicio1.c`):** La cadena de entrada con los movimientos se copia a un búfer reservado dinámicamente usando `malloc()` y se libera con `free()`. Esto permite tokenizar la cadena con `strtok` sin modificar el texto original y procesar secuencias de cientos de movimientos sin desbordar la pila (*stack overflow*).
- **En Python (`ejercicio1.py`):** El procesamiento se realiza mediante listas y manipulación de cadenas nativas, gestionadas en el heap por el recolector de basura de Python.
- **Nomenclatura:** Todo el código fue implementado utilizando nombres de variables y funciones en español (ej. `validar_secuencia`, `analizar_casilla`) para mantener una estructura clara y académica.

### 2.3. Complejidad Computacional
- **Complejidad Temporal:** $O(n)$, donde $n$ es el número de movimientos. Cada movimiento se analiza en tiempo constante $O(1)$.
- **Complejidad Espacial:** $O(n)$ para el almacenamiento dinámico del búfer de la cadena de entrada.

---

## 3. Estructura de Archivos

| Archivo | Descripción |
| :--- | :--- |
| `ejercicio1.py` | Implementación en Python 3 puro. |
| `ejercicio1.c` | Implementación en C estándar con memoria dinámica. |
| `resultado_ej1_py.txt` | Reporte generado automáticamente con los tiempos en Python. |
| `resultado_ej1_c.txt` | Reporte generado automáticamente con los tiempos en C. |
| `README.md` | Documentación técnica y académica del ejercicio. |

---

## 4. Instrucciones de Compilación y Ejecución

### En Python:
```bash
python ejercicio1.py

```
### En C (GCC / MinGW / Clang):
```bash
gcc ejercicio1.c -O2 -o ejercicio1
./ejercicio1
```
## 5. Casos de Prueba Oficiales de la Guía

A continuación se presentan los 9 casos de prueba estipulados en el enunciado, junto con la salida exacta que genera nuestro programa y su respectiva validación:

| # | Posición Inicial (Ak) | Cadena de Movimientos (C) | Salida Obtenida por el Programa | Estado |
|:---:|:---:|:---|:---|:---:|
| 1 | `a1` | `Kc2 Kd4 Kb3 Kc5` | `Caso 1: movimiento CORRECTO` | ✅ PASS |
| 2 | `a1` | `Kc2 Kd4 Kb4 Kc5` | `Caso 2: INCORRECTO falla en el movimiento 3` | ✅ PASS |
| 3 | `a2` | `Kc3 Ke4 Kf6 Ke8 Kg7` | `Caso 3: movimiento CORRECTO` | ✅ PASS |
| 4 | `a2` | `Kc8 Ke4 Kf6 Ke8 Kg7` | `Caso 4: INCORRECTO falla en el movimiento 1` | ✅ PASS |
| 5 | `a8` | `Kb6 Kd7` | `Caso 5: movimiento CORRECTO` | ✅ PASS |
| 6 | `a8` | `Kb6 Kb7` | `Caso 6: INCORRECTO falla en el movimiento 2` | ✅ PASS |
| 7 | `a1` | `Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kb4` | `Caso 7: movimiento CORRECTO` | ✅ PASS |
| 8 | `a1` | `Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4` | `Caso 8: INCORRECTO falla letra Q no pertenece a un caballo` | ✅ PASS |
| 9 | `a1` | `Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kh6 Kb4` | `Caso 9: INCORRECTO falla en el movimiento 9` | ✅ PASS |

## 6. Resultados de Rendimiento y Medición

Se realizaron las pruebas de estrés exigidas utilizando la lista de 500 movimientos suministrada en el enunciado (tomando $A_k = a2$ para iniciar de forma válida). Los reportes completos se encuentran en los archivos `resultado_ej1_c.txt` y `resultado_ej1_py.txt`.

| Métrica | Implementación en C | Implementación en Python |
| :--- | :--- | :--- |
| **$n = 100$ movimientos** | `0.000000 ms` | `0.167500 ms` |
| **10 iteraciones (500 mov.)** | `0.0000 ms` | `1.6272 ms` |
| **Estado final (500 mov.)** | `INCORRECTO` (detectado en el fallo) | `INCORRECTO` (detectado en el fallo) |

### Notas técnicas sobre los resultados:
1. **Resolución del reloj en C:** El tiempo de `0.000000 ms` en C es normal. La función `clock()` en Windows tiene una resolución de milisegundos. El procesamiento en C es tan eficiente que se completa en menos de un *tick* de reloj, por lo que se redondea a cero.
2. **Estado "INCORRECTO" en las 500 iteraciones:** La lista exacta suministrada en el PDF oficial contiene un salto inválido (error de tipeo en el documento original). Ambos programas detectaron este error y se detuvieron correctamente gracias al cortocircuito exigido en el enunciado, demostrando la efectividad de la validación.
