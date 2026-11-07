# Ejercicio 2: Generación de Polinomio $(x+1)^n$ con Triángulo de Pascal y Evaluación Dinámica

**Universidad Nacional Experimental de Guayana (UNEG)**  
**Coordinación de Ingeniería en Informática**  
**Lenguajes y Compiladores — Periodo 2026-II**  
**Estudiante:** Alexander Fernández  
**Profesor:** Msc. Félix Márquez  

---

## 1. Descripción del Problema
Dado un número entero no negativo $n$:
1. **a)** Generar los coeficientes del polinomio $(x+1)^n$ utilizando el **Triángulo de Pascal** implementado con **memoria dinámica**, y mostrar la representación algebraica resultante del polinomio.
2. **b)** Mostrar por pasos el cálculo para un valor $x$ dado, evaluando $f(x) = (x+1)^n$ de acuerdo con el polinomio generado.
3. **c)** Medir y comparar el tiempo necesario para generar los coeficientes para $n = 100$ desde un código Python vs un código C, registrando los resultados en sus respectivos archivos `.txt`.

---

## 2. Fundamento Matemático y Algorítmico

### 2.1. Teorema del Binomio y Triángulo de Pascal
Por el Teorema del Binomio de Newton:
$$(x + 1)^n = \sum_{k=0}^{n} \binom{n}{k} x^{n-k} 1^k = \binom{n}{0}x^n + \binom{n}{1}x^{n-1} + \dots + \binom{n}{n-1}x + \binom{n}{n}$$

Donde los coeficientes binomiales $\binom{n}{k}$ corresponden exactamente a la fila $n$ del Triángulo de Pascal:
- Fila 0: `1`
- Fila 1: `1  1`
- Fila 2: `1  2  1`
- Fila 3: `1  3  3  1`
- Fila 4: `1  4  6  4  1`
- Fila 5: `1  5 10 10  5  1`
- Fila 6: `1  6 15 20 15  6  1`
- Fila 7: `1  7 21 35 35 21  7  1`

La relación de recurrencia en el triángulo es:
$$C(n, k) = C(n - 1, k - 1) + C(n - 1, k) \quad \text{con } C(n, 0) = C(n, n) = 1$$

### 2.2. Gestión de Memoria Dinámica
- **En C (`pascal_polinomio.c`):**
  - Cada fila se crea dinámicamente con `malloc()`.
  - Al avanzar de fila, los punteros de la fila anterior se liberan con `free()` para evitar fugas de memoria (*memory leaks*).
  - Para $n = 100$, el coeficiente central $\binom{100}{50} \approx 1.0089 \times 10^{29}$ excede con creces la capacidad de un entero de 64 bits (`unsigned long long` soporta hasta $\approx 1.84 \times 10^{19}$). Por ende, se implementó una estructura **BigInt** estándar en C utilizando cadenas dinámicas y suma aritmética por dígitos con acarreo en memoria dinámica.
  - Utiliza el temporizador de alta resolución (`QueryPerformanceCounter`) para registrar tiempos exactos a nivel de microsegundos en `resultado_tiempos_c.txt`.
- **En Python (`pascal_polinomio.py`):**
  - Se utilizan listas dinámicas que alojan enteros de precisión arbitraria integrados en el lenguaje.
  - Guarda autónomamente sus mediciones en `resultado_tiempos_python.txt`.

### 2.3. Complejidad Computacional
- **Complejidad Temporal:** $O(n^2)$ para calcular todas las filas hasta $n$. Para $n=100$, son $100 \times 101 / 2 = 5050$ sumas, ejecutándose en fracciones de milisegundo.
- **Complejidad Espacial:** $O(n)$ utilizando memoria dinámica solo para las filas adyacentes activas.

---

## 3. Estructura de Archivos

| Archivo | Descripción |
| :--- | :--- |
| `pascal_polinomio.py` | Implementación completa en Python 3 puro. |
| `pascal_polinomio.c` | Implementación en C (ANSI/C99) con BigInt y memoria dinámica. |
| `resultado_tiempos_python.txt` | Resultados de medición y cálculo para Python. |
| `resultado_tiempos_c.txt` | Resultados de medición y cálculo para C. |
| `ejecutar.bat` | Script de compilación y ejecución en Windows. |
| `README.md` | Documentación técnica y explicativa. |

---

## 4. Instrucciones de Ejecución

### En Python:
```bash
python pascal_polinomio.py
```
*Para evaluar un valor arbitrario de $n$ y $x$:*
```bash
python pascal_polinomio.py 4 3
```

### En C (GCC / MinGW / Clang):
```bash
gcc -O2 pascal_polinomio.c -o pascal_polinomio.exe
pascal_polinomio.exe
```
*Para evaluar en C:*
```bash
pascal_polinomio.exe 4 3
```

---

## 5. Medición Comparativa para $n = 100$

| Métrica | Python 3 | Lenguaje C |
| :--- | :--- | :--- |
| **Tiempo de Generación** | $\approx 0.32\text{ ms}$ | $\approx 0.51\text{ ms}$ (con BigInt dinámico) |
| **Precisión Numérica** | Exacta (Arbitrary Precision nativo) | Exacta (BigInt dinámico propio) |
| **Coeficiente $\binom{100}{50}$** | `100891344545564193334812497256` | `100891344545564193334812497256` |
| **Total de Coeficientes** | 101 | 101 |
