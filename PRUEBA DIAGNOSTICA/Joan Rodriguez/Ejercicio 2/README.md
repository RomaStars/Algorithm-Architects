# Ejercicio 2: Expansión de Binomio $(x+1)^n$ mediante Triángulo de Pascal

**Universidad Nacional Experimental de Guayana**  
**Coordinación de Ingeniería en Informática**  
**Lenguajes y Compiladores — Periodo 2026-II**  
**Estudiante:** Joan Rodríguez  
**Profesor:** Msc. Félix Márquez  

---

## 1. Descripción del Problema

Dado un entero $n \geq 0$ y un valor $x$, el programa debe:

1. **Generar los coeficientes** del polinomio $(x+1)^n$ utilizando la fila $n$ del Triángulo de Pascal.
2. **Mostrar el polinomio expandido** en notación algebraica estándar (ej. `x^5 + 5x^4 + 10x^3 + 10x^2 + 5x + 1`).
3. **Evaluar paso a paso** $f(x) = (x+1)^n$ mostrando cada término calculado individualmente y la suma total.
4. **Medir el rendimiento** de la generación de coeficientes para $n = 100$.

Se implementó en **Python** y **C** para comparar la gestión de memoria dinámica entre un lenguaje interpretado con recolector de basura y un lenguaje compilado con manejo manual de memoria (`malloc`/`free`).

---

## 2. Fundamento Teórico y Algorítmico

### 2.1. Triángulo de Pascal y Teorema del Binomio

El Teorema del Binomio establece que:

$$(x+1)^n = \sum_{k=0}^{n} \binom{n}{k} x^{n-k}$$

Donde los coeficientes binomiales $\binom{n}{k}$ corresponden a la fila $n$ del Triángulo de Pascal, construidos iterativamente con la recurrencia:

$$\binom{n}{k} = \binom{n-1}{k-1} + \binom{n-1}{k}$$

### 2.2. Algoritmo Iterativo

En lugar de calcular factoriales (costoso y propenso a desbordamiento), se construye la fila $n$ de forma incremental:

1. Se parte de la fila 0: `[1]`.
2. Para cada fila $i$ de 1 a $n$, se reserva dinámicamente un arreglo de tamaño $i+1$.
3. Los extremos valen 1; los valores intermedios son la suma de los dos superiores adyacentes.
4. Se libera la fila anterior (en C con `free()`; en Python el recolector de basura lo gestiona automáticamente).

### 2.3. Gestión de Memoria Dinámica

| Aspecto | Python | C |
| :--- | :--- | :--- |
| **Reserva** | `[1] * (i + 1)` — lista dinámica en el heap | `malloc((i + 1) * sizeof(double))` |
| **Liberación** | Automática (recolector de basura) | Manual con `free(fila_ant)` y `free(parciales)` |
| **Riesgo de fuga** | Ninguno | Controlado — se libera en cada iteración |

### 2.4. Complejidad Computacional

- **Complejidad Temporal:** $O(n^2)$ — se recorren todas las filas del triángulo hasta la fila $n$.
- **Complejidad Espacial:** $O(n)$ — solo se mantienen dos filas en memoria simultáneamente.

---

## 3. Estructura de Archivos

| Archivo | Descripción |
| :--- | :--- |
| `ejercicio2.py` | Implementación en Python 3. |
| `ejercicio2.c` | Implementación en C con `malloc`/`free`. |
| `resultado_ej2.txt` | Reporte con las salidas de ambas implementaciones. |
| `README.md` | Documentación técnica y académica del ejercicio. |

---

## 4. Instrucciones de Ejecución

### En Python:
```bash
python ejercicio2.py
```

### En C:
```bash
gcc ejercicio2.c -o ejercicio2 -lm
./ejercicio2
```

---

## 5. Prueba Funcional: $(x+1)^5$ evaluado en $x = 2$

Ambas implementaciones generan la misma expansión y evaluación paso a paso:

**Coeficientes generados (fila 5 de Pascal):**
```
[1, 5, 10, 10, 5, 1]
```

**Polinomio expandido:**
```
(x+1)^5 = x^5 + 5x^4 + 10x^3 + 10x^2 + 5x + 1
```

**Evaluación paso a paso de $f(2) = (2+1)^5 = 3^5 = 243$:**

| Paso | Coeficiente | Potencia | Cálculo | Resultado |
|:---:|:---:|:---:|:---|:---:|
| 1 | 1 | $2^5 = 32$ | $1 \times 32$ | 32 |
| 2 | 5 | $2^4 = 16$ | $5 \times 16$ | 80 |
| 3 | 10 | $2^3 = 8$ | $10 \times 8$ | 80 |
| 4 | 10 | $2^2 = 4$ | $10 \times 4$ | 40 |
| 5 | 5 | $2^1 = 2$ | $5 \times 2$ | 10 |
| 6 | 1 | $2^0 = 1$ | $1 \times 1$ | 1 |

$$f(2) = 32 + 80 + 80 + 40 + 10 + 1 = 243 \quad \checkmark$$

---

## 6. Resultados de Rendimiento y Medición

Generación de los 101 coeficientes de $(x+1)^{100}$:

| Métrica | Python | C |
| :--- | :--- | :--- |
| **Coeficientes generados** | 101 | 101 |
| **Coeficiente central $\binom{100}{50}$** | `100891344545564193334812497256` | `100891344545564237256087044096` |
| **Tiempo de generación** | `0.4868 ms` | `0.0292 ms` (~29.20 µs) |
| **Speedup de C sobre Python** | — | ~16.7× más rápido |

> **Nota sobre precisión:** La diferencia en el coeficiente central $\binom{100}{50}$ se debe a que Python maneja enteros de precisión arbitraria (valor exacto), mientras que C usa `double` (64 bits IEEE 754) que pierde precisión para enteros mayores a $2^{53}$. El valor exacto es el reportado por Python.

---

## 7. Análisis Comparativo

1. **Rendimiento:** C es ~16.7× más rápido que Python para la generación de coeficientes, gracias a la compilación nativa y la ausencia de sobrecarga del intérprete.
2. **Precisión:** Python maneja enteros de precisión arbitraria de forma nativa, mientras que C con `double` pierde precisión para valores grandes. Para exactitud en coeficientes grandes, Python es la mejor opción.
3. **Gestión de memoria:** En C se controla explícitamente cada `malloc`/`free`, lo que permite optimizar el uso de memoria pero exige disciplina para evitar fugas. Python delega esta responsabilidad al recolector de basura.
