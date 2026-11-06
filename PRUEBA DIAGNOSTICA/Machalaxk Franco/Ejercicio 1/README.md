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

En el tablero se encuentra un único caballo con posición inicial $A_k$. Se recibe una cadena $C$ con $n$ movimientos en notación abreviada (prefijo `K` seguido de la columna y fila destino, ej. `Kc2`).

El programa debe verificar secuencialmente los movimientos e indicar:
1. Si todos son correctos: `"movimiento CORRECTO."`
2. Si un movimiento contiene un identificador que no corresponde al caballo (por ejemplo `Qb4`):  
   `"INCORRECTO falla letra {letra} no pertenece a un caballo."`
3. Si un movimiento es inválido (fuera del tablero o no cumple el patrón en "L"):  
   `"INCORRECTO falla en el movimiento {i}."`
4. El análisis se detiene inmediatamente al encontrar el primer fallo (evaluación en cortocircuito).

*Nota: Se seleccionó **Python** para esta implementación por su manejo limpio de cadenas y estructuras de datos dinámicas, cumpliendo con el lineamiento de realizarlo en el lenguaje de preferencia.*

---

## 2. Fundamento Teórico y Algorítmico

### 2.1. Regla de Movimiento del Caballo
En ajedrez, el caballo se desplaza en forma de "L", lo que equivale matemáticamente a una distancia métrica en el plano discreto de:
$$\Delta x^2 + \Delta y^2 = 5$$

O expresado en diferencias absolutas entre coordenadas:
$$(|\Delta \text{columna}| = 1 \land |\Delta \text{fila}| = 2) \quad \lor \quad (|\Delta \text{columna}| = 2 \land |\Delta \text{fila}| = 1)$$

### 2.2. Algoritmo y Memoria Dinámica
- **Procesamiento:** El programa recibe las cadenas de texto, las divide dinámicamente en una lista de tokens usando `split()`, y valida cada movimiento en tiempo constante $O(1)$.
- **Cortocircuito:** Si encuentra un error, el bucle `for` se rompe inmediatamente y retorna el número de movimiento donde falló, evitando procesar el resto de la cadena innecesariamente.
- **Gestión de memoria:** En Python, la asignación de la lista de tokens se realiza de forma dinámica en el *heap* administrado por el recolector de basura del intérprete.

### 2.3. Complejidad Computacional
- **Complejidad Temporal:** $O(n)$, donde $n$ es el número de movimientos. Cada movimiento se analiza una sola vez.
- **Complejidad Espacial:** $O(n)$ para el almacenamiento dinámico de los tokens en la memoria.

---

## 3. Estructura de Archivos

| Archivo | Descripción |
| :--- | :--- |
| `ejercicio1.py` | Implementación del algoritmo en Python 3. |
| `resultado_ej1_py.txt` | Reporte generado automáticamente con las pruebas y la medición de tiempos. |
| `README.md` | Documentación técnica y académica del ejercicio. |

---

## 4. Instrucciones de Ejecución

### En Python:
```bash
python ejercicio1.py
```
----

## 5. Casos de Prueba Oficiales de la Guía

El programa ejecuta automáticamente los 9 casos de prueba estipulados en el enunciado y genera la salida exacta solicitada:

| # | Posición Inicial (Ak) | n | Cadena de Movimientos (C) | Salida Obtenida | Estado |
|:---:|:---:|:---:|:---|:---|:---:|
| 1 | `a1` | 4 | `Kc2 Kd4 Kb3 Kc5` | `movimiento CORRECTO.` | ✅ PASS |
| 2 | `a1` | 4 | `Kc2 Kd4 Kb4 Kc5` | `INCORRECTO falla en el movimiento 3.` | ✅ PASS |
| 3 | `a2` | 5 | `Kc3 Ke4 Kf6 Ke8 Kg7` | `movimiento CORRECTO.` | ✅ PASS |
| 4 | `a2` | 5 | `Kc8 Ke4 Kf6 Ke8 Kg7` | `INCORRECTO falla en el movimiento 1.` | ✅ PASS |
| 5 | `a8` | 2 | `Kb6 Kd7` | `movimiento CORRECTO.` | ✅ PASS |
| 6 | `a8` | 2 | `Kb6 Kb7` | `INCORRECTO falla en el movimiento 2.` | ✅ PASS |
| 7 | `a1` | 10 | `Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kb4` | `movimiento CORRECTO.` | ✅ PASS |
| 8 | `a1` | 10 | `Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4` | `INCORRECTO falla letra Q no pertenece a un caballo.` | ✅ PASS |
| 9 | `a1` | 10 | `Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kh6 Kb4` | `INCORRECTO falla en el movimiento 9.` | ✅ PASS |

---

## 6. Resultados de Rendimiento y Medición

Se realizó la prueba de estrés exigida en el enunciado: **verificar 10 veces la lista de 500 movimientos**

| Métrica | Implementación en Python |
| :--- | :--- |
| **Lista evaluada** | 500 movimientos |
| **Iteraciones** | 10 pasadas |
| **Estado final** | `movimiento CORRECTO.` |
| **Tiempo total (10 pasadas)** | `4.7663 ms` |
| **Tiempo promedio por pasada** | `0.4766 ms` |

1. **Validación de la lista actualizada:** El profesor corrigió la lista de movimientos en la actualización del PDF. Al ser una lista 100% válida, el programa procesó las 10 pasadas completas sin detenerse en errores, arrojando un estado final `CORRECTO`.
2. **Eficiencia:** El tiempo promedio por pasada de los 500 movimientos es de apenas `0.4766 ms`. Esto demuestra la eficiencia del algoritmo de validación en tiempo lineal $O(n)$, procesando cada movimiento sin bucles anidados ni sobrecarga innecesaria.
