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

El programa verifica secuencialmente los movimientos e indica:
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

### 2.2. Implementación en Python
- **Estructura y Gestión de Memoria:** Se procesan las cadenas de entrada mediante listas de tokens asignadas dinámicamente en el heap, utilizando exclusivamente las funciones de la biblioteca estándar de Python (sin dependencias externas).
- **Rutas Autónomas y Sobreescritura:** El script resuelve dinámicamente su directorio de trabajo (`BASE_DIR = os.path.dirname(os.path.abspath(__file__))`), garantizando que el archivo de reporte `resultado_tiempos_python.txt` se genere y sobreescriba siempre dentro de la carpeta del ejercicio, sin importar desde qué directorio se ejecute el comando.

### 2.3. Complejidad Computacional
- **Complejidad Temporal:** $O(n)$, donde $n$ es el número de movimientos. Cada validación de salto se evalúa en tiempo constante $O(1)$.
- **Complejidad Espacial:** $O(n)$ para almacenar en memoria dinámica la secuencia de tokens a validar.

---

## 3. Estructura de Archivos

| Archivo | Descripción |
| :--- | :--- |
| `caballo.py` | Implementación completa en Python 3 estándar (sin dependencias de terceros). |
| `resultado_tiempos_python.txt` | Reporte generado con los tiempos de ejecución y pruebas de validación. |
| `ejecutar.bat` | Script por lotes para ejecutar automáticamente la solución en Windows. |
| `README.md` | Documentación técnica y académica del ejercicio. |

---

## 4. Instrucciones de Ejecución

### Ejecución directa desde consola:
```bash
python caballo.py
```

### Ejecutar caso personalizado pasando argumentos por consola:
```bash
python caballo.py a1 "Kc2 Kd4 Kb3 Kc5"
```

O haciendo doble clic en el archivo `ejecutar.bat`.

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

## 6. Resultados de Rendimiento (Python 3)
- **Verificación para $n = 100$ movimientos:** $\approx 0.055\text{ ms}$ ($0.000055\text{ s}$).
- **10 iteraciones de la secuencia de la guía (330 movimientos, $A_k = a2$):** $\approx 1.38\text{ ms}$ en total (promedio de $0.138\text{ ms}$ por pasada).
- **10 iteraciones de 500 movimientos continuos ($A_k = a2$):** $\approx 2.60\text{ ms}$ en total (promedio de $0.260\text{ ms}$ por pasada).
