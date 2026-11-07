# Ejercicio 2: Generación y Evaluación del Polinomio $(x+1)^n$ mediante el Triángulo de Pascal (C vs. Python)

**Universidad Nacional Experimental de Guayana (UNEG)**  
**Vicerrectorado Académico**  
**Coordinación de Ingeniería en Informática**  
**Asignatura:** Lenguajes y Compiladores (Periodo Lectivo 2026-II)  
**Profesor:** Msc. Félix Márquez  

---

## 📋 1. Descripción del Problema

Dado un número entero no negativo $n$, el ejercicio requiere:

1. **Generación de Coeficientes:** Calcular los coeficientes binomiales de la expansión del polinomio $(x+1)^n$ haciendo uso de la estructura aditiva del **Triángulo de Pascal**. La solución en C debe implementar **gestión dinámica de memoria**.
2. **Representación Polinómica:** Formatear y mostrar en pantalla la expresión matemática completa $f(x) = (x+1)^n$.
3. **Evaluación Paso a Paso:** Dada una variable $x \in \mathbb{R}$, calcular y mostrar el desglose término a término del polinomio, sumando cada contribución parcial y comparando el resultado final contra la evaluación directa $(x+1)^n$.
4. **Benchmark Comparativo:** Comparar el tiempo de ejecución necesario para calcular los coeficientes de $n = 100$ con $10,000$ repeticiones entre una implementación en **Lenguaje C** y una en **Python**.
5. **Persistencia de Resultados:** Exportar automáticamente un informe en un archivo de texto plano (`resultados.txt`) tras la ejecución del benchmark en ambos lenguajes.

---

## 🧠 2. Fundamento Teórico y Algorítmico

### 2.1 Expansión Polinómica y Triángulo de Pascal
De acuerdo con el teorema del binomio de Newton, la expansión de $(x+1)^n$ viene dada por:

$$(x+1)^n = \sum_{k=0}^{n} \binom{n}{k} x^{n-k}$$

Donde los coeficientes binomiales $\binom{n}{k}$ equivalen exactamente a los elementos de la fila $n$ del Triángulo de Pascal. 

En lugar de calcular los factoriales directamente (lo que provocaría desbordamientos de entero prematuros), construimos secuencialmente cada elemento de la fila usando la relación de recurrencia en un solo arreglo:

$$\text{row}[j] = \text{row}[j] + \text{row}[j-1]$$

### 2.2 Explicación del Código por Componentes

#### 🔹 Implementación en Lenguaje C (`pascal_poly.c`)

1. **Gestión de Memoria Dinámica (`generate_pascal_coefficients`):**
   * Reservamos espacio dinámico en el *heap* mediante `malloc` para $(n + 1)$ elementos de tipo `unsigned long long`:
     ```c
     unsigned long long *row = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
     ```
   * Se evalúa de forma iterativa desde $i = 1$ hasta $n$, actualizando los coeficientes de derecha a izquierda para no sobrescribir valores requeridos en la misma fila.
2. **Impresión Formateada (`print_polynomial`):**
   * Recorre el arreglo de coeficientes adaptando el texto según las reglas de notación algebraicas (ocultando $x^0$, imprimiendo $x$ en lugar de $x^1$, y omitiendo el coeficiente $1$ si acompaña a una potencia).
3. **Evaluación Término a Término (`evaluate_polynomial_step_by_step`):**
   * Para cada término $i$, calcula $c_i \cdot x^{n-i}$ utilizando `pow()` de `<math.h>`, acumulando la suma y comparándola al final contra `pow(x + 1.0, n)`.
4. **Benchmark y Persistencia (`run_benchmark_c`):**
   * Mide el tiempo mediante `clock()` al ejecutar $10,000$ veces la generación y liberación de memoria (`free(coeffs)`). Exporta los resultados usando flujos de archivo en C (`fopen`, `fprintf`, `fclose`).

#### 🔹 Implementación en Python (`pascal_poly.py`)

1. **Construcción de Listas Dinámicas (`generate_pascal_coefficients`):**
   * Utiliza comprensiones de listas (*list comprehensions*) para construir iterativamente cada fila del triángulo:
     ```python
     row = [1] + [row[j] + row[j + 1] for j in range(len(row) - 1)] + [1]
     ```
2. **Medición con Alta Precisión (`run_benchmark_python`):**
   * Utiliza `time.perf_counter()` para obtener mediciones temporales de precisión nanosegunda, registrando y guardando los resultados en `resultados.txt` mediante la sentencia contextual `with open(...)`.

---

## 🗂️ 3. Estructura de Archivos

La arquitectura del proyecto separa modularmente las versiones de C y Python:

```text
EJERCICIO2/
├── README.md
├── c/
│   ├── Makefile
│   ├── include/
│   │   └── pascal_poly.h
│   └── src/
│       ├── main.c
│       └── pascal_poly.c
└── python/
    ├── main.py
    └── pascal_poly.py
```

---

## 🚀 4. Instrucciones de Compilación y Ejecución (Windows)

### Requisitos Previos
* Compilador **GCC** instalado (vía MinGW-w64, WinLibs o w64devkit).
* **Python 3.x** instalado.

---

### 4.1 Ejecución de la Versión en C

#### Opción A: Usando `make` (Recomendado)
Abre la terminal en el directorio `c/` y ejecuta:
```cmd
cd c
make
.\pascal_poly.exe
```

#### Opción B: Compilación Manual con GCC
```powershell
cd c
gcc -Wall -Wextra -std=c99 -Iinclude src/main.c src/pascal_poly.c -o pascal_poly.exe -lm
.\pascal_poly.exe
```
> **Nota:** Se creará automáticamente el archivo `c/resultados.txt`.

---

### 4.2 Ejecución de la Versión en Python

Abre la terminal en el directorio `python/` y ejecuta:
```powershell
cd python
python main.py
```
> **Nota:** Se creará automáticamente el archivo `python/resultados.txt`.

---

## 🧪 5. Casos de Prueba en la Guía

El caso base ejecutado para la demostración corresponde a **$n = 5$** y **$x = 2.0$**:

### 5.1 Fila del Triángulo de Pascal ($n = 5$)
$$\text{Coeficientes binomiales: } [1, 5, 10, 10, 5, 1]$$

### 5.2 Salida del Polinomio Formateado
$$f(x) = (x + 1)^5 = x^5 + 5x^4 + 10x^3 + 10x^2 + 5x + 1$$

### 5.3 Desglose de Evaluaciones para $x = 2.0$

| Término | Expresión Evaluada | Cálculo Numérico | Subtotal Parcial |
| :---: | :---: | :---: | :---: |
| **Término 1** | $1 \cdot (2.00)^5$ | $1 \cdot 32.0000$ | $32.0000$ |
| **Término 2** | $5 \cdot (2.00)^4$ | $5 \cdot 16.0000$ | $80.0000$ |
| **Término 3** | $10 \cdot (2.00)^3$ | $10 \cdot 8.0000$ | $80.0000$ |
| **Término 4** | $10 \cdot (2.00)^2$ | $10 \cdot 4.0000$ | $40.0000$ |
| **Término 5** | $5 \cdot (2.00)^1$ | $5 \cdot 2.0000$ | $10.0000$ |
| **Término 6** | $1 \cdot (2.00)^0$ | $1 \cdot 1.0000$ | $1.0000$ |

* **Suma por polinomio:** $32.0000 + 80.0000 + 80.0000 + 40.0000 + 10.0000 + 1.0000 = \mathbf{243.0000}$
* **Verificación directa $(2 + 1)^5 = 3^5$:** $\mathbf{243.0000}$

---

## 📊 6. Resultados de Rendimiento (Benchmark C vs. Python)

Métricas obtenidas al ejecutar el algoritmo para **$n = 100$** durante **$10,000$ repeticiones**:

| Lenguaje | Parámetro $n$ | Repeticiones | Tiempo Total (s) | Tiempo Promedio / Ejecución | Estado y Archivo |
| :--- | :---: | :---: | :---: | :---: | :---: |
| **Lenguaje C** | 100 | 10,000 | $\approx 0.111000\text{ s}$ | $\approx 0.00001110\text{ ms}$ | `c/resultados.txt` |
| **Python 3** | 100 | 10,000 | $\approx 2.816892\text{ s}$ | $\approx 0.00028169\text{ ms}$ | `python/resultados.txt` |

### Análisis Comparativo:
1. **Eficiencia en C:** El programa en Lenguaje C resulta ser entre **35 y 40 veces más rápido** que el de Python. Esto se debe a la compilación directa a código máquina binario, la ausencia de capas de interpretación y la gestión manual de arreglos en memoria estática/heap mediante `malloc`.
2. **Comportamiento en Python:** Python introduce una sobrecarga (*overhead*) debido al tipado dinámico, gestión de objetos en memoria y recolección de basura (*Garbage Collector*). A pesar de ello, la legibilidad del código resulta altamente concisa.
3. Ambos programas exportan exitosamente las métricas obtenidas al archivo `resultados.txt` en sus respectivas carpetas.