# Ejercicio 2: Polinomio (x+1)^n y Evaluación con Memoria Dinámica

**Universidad Nacional Experimental de Guayana**  
**Coordinación de Ingeniería en Informática**  
**Lenguajes y Compiladores — Periodo 2026-II**  
**Estudiante:** Mchalaxk Franco  
**Profesor:** Msc. Félix Márquez  

---

## 1. Descripción del Problema
Dado un número entero no negativo $n$, el programa debe:
1. **Generar los coeficientes** del polinomio $(x+1)^n$ utilizando el Triángulo de Pascal y mostrar el polinomio resultante.
2. **Mostrar por pasos** el cálculo de $f(x) = (x+1)^n$ para un valor de $x$ dado, según los coeficientes generados.
3. **Implementar el algoritmo utilizando memoria dinámica** para el manejo de los coeficientes.
4. **Medir el tiempo de ejecución** para la generación del polinomio con $n=100$ en C y en Python.

---

## 2. Fundamento Teórico y Algorítmico

### 2.1. Triángulo de Pascal
Los coeficientes del polinomio $(x+1)^n$ corresponden a la fila $n$ del Triángulo de Pascal. Cada coeficiente se calcula mediante la relación de recurrencia:
$$C(n, k) = C(n-1, k-1) + C(n-1, k)$$
Para optimizar el espacio, el algoritmo construye la fila de forma **in-place** (en el mismo arreglo), recorriendo de mayor a menor ($j = k \dots 1$) para no sobrescribir los valores que aún se necesitan.

### 2.2. Gestión de Memoria Dinámica
- **En C (`ejercicio2.c`):** Para $n=100$, los coeficientes superan los 30 dígitos. Como los tipos primitivos de C no soportan esto, se implementó un **Entero Grande** (BigInt) dinámico en base $10^9$. La memoria para los dígitos se reserva y redimensiona dinámicamente usando `malloc()` y `realloc()`, y se libera con `free()`.
- **En Python (`ejercicio2.py`):** Python maneja enteros de precisión arbitraria de forma nativa (asignados dinámicamente en el heap), por lo que el cálculo es directo sin necesidad de estructuras adicionales.

### 2.3. Complejidad Computacional
- **Construcción del Triángulo:** $O(n^2)$ sumas.
- **Evaluación del Polinomio:** $O(n)$ multiplicaciones.
- **Complejidad Espacial:** $O(n)$ para almacenar la fila del triángulo.

---

## 3. Estructura de Archivos

| Archivo | Descripción |
| :--- | :--- |
| `ejercicio2.py` | Implementación en Python 3 puro. |
| `ejercicio2.c` | Implementación en C estándar con Entero Grande dinámico. |
| `resultado_ej2_py.txt` | Reporte generado automáticamente con la demostración y tiempos en Python. |
| `resultado_ej2_c.txt` | Reporte generado automáticamente con la demostración y tiempos en C. |
| `README.md` | Documentación técnica y académica del ejercicio. |

---

## 4. Instrucciones de Compilación y Ejecución

### En Python:
```bash
python ejercicio2.py

```
### En C (GCC / MinGW / Clang):
```bash
gcc ejercicio2.c -O2 -o ejercicio2
./ejercicio2gcc ejercicio2.c -O2 -o ejercicio2
./ejercicio2
```

---

## 5. Verificación del Funcionamiento (Caso Demostrativo)

Para evidenciar el correcto funcionamiento, ambos programas evalúan automáticamente el caso $n=5$ y $x=2$. El reporte generado en los archivos `.txt` muestra paso a paso el cálculo:

| Elemento | Resultado Obtenido por el Programa | Estado |
| :--- | :--- | :---: |
| **Polinomio generado** | `x^5 + 5x^4 + 10x^3 + 10x^2 + 5x + 1` | ✅ PASS |
| **Coeficientes (Pascal)** | `1 5 10 10 5 1` | ✅ PASS |
| **Paso 0** | `c_0 * x^0 = 1 * 1 = 1` | ✅ PASS |
| **Paso 1** | `c_1 * x^1 = 5 * 2 = 10` | ✅ PASS |
| **Paso 2** | `c_2 * x^2 = 10 * 4 = 40` | ✅ PASS |
| **Paso 3** | `c_3 * x^3 = 10 * 8 = 80` | ✅ PASS |
| **Paso 4** | `c_4 * x^4 = 5 * 16 = 80` | ✅ PASS |
| **Paso 5** | `c_5 * x^5 = 1 * 32 = 32` | ✅ PASS |
| **Resultado Final f(2)** | `243` *(equivalente a 3^5)* | ✅ PASS |

--- 

## 6. Resultados de Rendimiento y Medición

Se realizaron las pruebas de estrés generando el polinomio para $n=100$ un total de 100 veces. Los reportes completos se encuentran en los archivos `resultado_ej2_c.txt` y `resultado_ej2_py.txt`.

| Métrica | Implementación en C | Implementación en Python |
| :--- | :--- | :--- |
| **Generación de n=100 (100 rep.)** | `16.000000 ms` | `25.237700 ms` |
| **Tiempo promedio por repetición** | `0.160000 ms` | `0.252377 ms` |
