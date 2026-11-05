# Ejercicio 1: Verificación de Movimientos de Caballo en Ajedrez

**Universidad Nacional Experimental de Guayana (UNEG)**  
**Coordinación de Ingeniería en Informática**  
**Lenguajes y Compiladores — Periodo 2026-II**  
**Estudiante:** Alexander Fernández  
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

### 2.2. Gestión de Memoria Dinámica
- **En C (`caballo.c`):** La cadena de entrada que contiene los movimientos se almacena y tokeniza en memoria dinámica utilizando `malloc()` y `free()`. Esto permite procesar cadenas arbitrariamente largas (como secuencias de cientos de movimientos) sin riesgos de desbordamiento de búfer en la pila (*stack overflow*).
- **En Python (`caballo.py`):** Se realiza el procesamiento nativo mediante listas de tokens asignadas dinámicamente en el heap por el recolector de memoria de Python.

### 2.3. Complejidad Computacional
- **Complejidad Temporal:** $O(n)$, donde $n$ es el número de movimientos. Cada movimiento se analiza en tiempo constante $O(1)$.
- **Complejidad Espacial:** $O(n)$ para el almacenamiento dinámico del búfer de la cadena de entrada.

---

## 3. Estructura de Archivos

| Archivo | Descripción |
| :--- | :--- |
| `caballo.py` | Implementación en Python 3 puro (estándar, sin librerías de terceros). |
| `caballo.c` | Implementación en C estándar (ANSI C / C99) con memoria dinámica. |
| `resultado_tiempos.txt` | Archivo con los resultados de las mediciones de tiempo y pruebas. |
| `ejecutar.bat` | Script de automatización para compilar en C y ejecutar en Python/C. |
| `README.md` | Documentación técnica y académica del ejercicio. |

---

## 4. Instrucciones de Compilación y Ejecución

### En Python:
```bash
python caballo.py
```
*Para verificar un caso personalizado desde consola:*
```bash
python caballo.py a1 "Kc2 Kd4 Kb3 Kc5"
```

### En C (GCC / MinGW / Clang):
```bash
gcc -O2 caballo.c -o caballo.exe
caballo.exe
```
*Para verificar un caso personalizado en C:*
```bash
caballo.exe a1 "Kc2 Kd4 Kb3 Kc5"
```

---

## 5. Casos de Prueba Oficiales de la Guía

| # | $A_k$ | Cadena $C$ | Salida Obtenida | Estado |
|---|---|---|---|---|
| 1 | `a1` | `Kc2 Kd4 Kb3 Kc5` | `movimiento CORRECTO.` | PASS |
| 2 | `a1` | `Kc2 Kd4 Kb4 Kc5` | `movimiento INCORRECTO falla en el movimiento 3.` | PASS |
| 3 | `a2` | `Kc3 Ke4 Kf6 Ke8 Kg7` | `movimiento CORRECTO.` | PASS |
| 4 | `a2` | `Kc8 Ke4 Kf6 Ke8 Kg7` | `movimiento INCORRECTO falla en el movimiento 1.` | PASS |
| 5 | `a8` | `Kb6 Kd7` | `movimiento CORRECTO.` | PASS |
| 6 | `a8` | `Kb6 Kb7` | `movimiento INCORRECTO falla en el movimiento 2.` | PASS |
| 7 | `a1` | `Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kb4` | `movimiento CORRECTO.` | PASS |
| 8 | `a1` | `Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4` | `movimiento INCORRECTO falla letra Q no pertenece a un caballo.` | PASS |
| 9 | `a1` | `Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kh6 Kb4` | `movimiento INCORRECTO falla en el movimiento 9.` | PASS |

---

## 6. Resultados de Rendimiento
- **$n = 100$ movimientos:** Tiempo de ejecución $\approx 0.0565\text{ ms}$ (Python) / $< 0.01\text{ ms}$ (C).
- **10 iteraciones de los movimientos de la guía:** $\approx 1.42\text{ ms}$ en total (promedio $0.14\text{ ms}$ por iteración).

