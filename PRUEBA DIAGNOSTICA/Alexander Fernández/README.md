# Repositorio de Prueba Diagnóstica — Alexander Fernández

**Universidad Nacional Experimental de Guayana (UNEG)**  
**Vicerrectorado Académico — Coordinación de Ingeniería en Informática**  
**Cátedra:** Lenguajes y Compiladores  
**Docente:** Msc. Félix Márquez  
**Periodo Lectivo:** 2026-II  
**Estudiante:** Alexander Fernández  
**Equipo:** Algorithm-Architects  

---

## Enlace al Video de Defensa (5%)
El enlace de Google Drive con la defensa individual en video del estudiante se encuentra documentado en:
📁 [ENLACE_DEFENSA.txt](file:///C:/Users/Alex/Algorithm-Architects/PRUEBA%20DIAGNOSTICA/Alexander%20Fern%C3%A1ndez/ENLACE_DEFENSA.txt)

---

## Estructura del Repositorio

El proyecto está organizado en tres carpetas según los lineamientos de la evaluación:

```
PRUEBA DIAGNOSTICA/Alexander Fernández/
│
├── ENLACE_DEFENSA.txt                 # Enlace al video de defensa en Google Drive
├── README.md                           # Documentación general del estudiante
│
├── Ejercicio 1/                        # Verificación de Movimientos de Caballo en Ajedrez
│   ├── caballo.py                      # Implementación en Python 3 estándar
│   ├── resultado_tiempos_python.txt    # Resultados y mediciones de tiempo en Python
│   ├── ejecutar.bat                    # Script de ejecución automática
│   └── README.md                       # Explicación teórica y complejidad O(n)
│
├── Ejercicio 2/                        # Polinomio (x+1)^n con Triángulo de Pascal y Memoria Dinámica
│   ├── pascal_polinomio.py             # Implementación en Python 3 estándar
│   ├── pascal_polinomio.c              # Implementación en C (ANSI/C99) con BigInt dinámico
│   ├── resultado_tiempos_python.txt    # Tiempos para n=100 y evaluación en Python
│   ├── resultado_tiempos_c.txt         # Tiempos para n=100 y evaluación en C
│   ├── ejecutar.bat                    # Script de compilación y ejecución automática
│   └── README.md                       # Explicación matemática y paso a paso
│
└── Ejercicio 3/                        # Analizador Léxico y Traductor de Palabras Reservadas en C
    ├── traductor_c.c                   # Analizador léxico y traductor en C en memoria dinámica
    ├── programa_prueba.c               # Código C de prueba con funciones, structs y strings
    ├── programa_traducido_c.c          # Código resultante traducido por C
    ├── resultado_traduccion_c.txt      # Reporte de análisis, frecuencias y tiempos en C
    ├── ejecutar.bat                    # Script de compilación y ejecución automática
    └── README.md                       # Documentación del autómata léxico
```

---

## Resumen de los Ejercicios Implementados

### 1. Ejercicio 1: Verificador de Movimientos de Caballo (Python 3)
- **Propósito:** Valida si una secuencia $C$ de saltos de caballo en notación ajedrecística (`Kc2`, `Kd4`, etc.) es legal partiendo de una casilla inicial $A_k$.
- **Lógica:** Implementa la distancia métrica del caballo $|\Delta x| \cdot |\Delta y| = 2$ en el tablero $8 \times 8$. Se detiene en cortocircuito al primer error y valida el prefijo `K` (reportando si otra letra como `Qb4` aparece).
- **Medición de Tiempos:** Evalúa para $n=100$ y realiza 10 repeticiones continuas sobre la secuencia provista en la guía académica.

### 2. Ejercicio 2: Generación de Polinomio $(x+1)^n$ con Triángulo de Pascal (Python y C)
- **Propósito:** Genera algebraicamente los coeficientes de $(x+1)^n$ usando memoria dinámica y muestra la evaluación detallada paso a paso de $f(x)$ para un valor $x$ dado.
- **Memoria Dinámica & BigInt en C:** Se implementó aritmética de enteros gigantes con cadenas dinámicas (`malloc`/`free`) para evitar desbordamientos de 64 bits en coeficientes que alcanzan el orden de $10^{29}$ para $n=100$.
- **Benchmark:** Comparación del tiempo de cálculo de la fila $n=100$ en Python ($\approx 0.32\text{ ms}$) frente a C ($\approx 0.51\text{ ms}$).

### 3. Ejercicio 3: Analizador Léxico y Traductor de Palabras Reservadas (Lenguaje C)
- **Propósito:** Carga dinámicamente un archivo fuente en lenguaje C en memoria (`malloc`/`fread`) e identifica palabras reservadas de la norma C99/C11/ANSI mediante un analizador léxico discriminativo que ignora cadenas literales (`"..."`) y comentarios (`//...`, `/*...*/`).
- **Traducción:** Sustituye las 37 palabras reservadas estándar de C por su contraparte en español (ej. `if` $\to$ `si`, `while` $\to$ `mientras`, `struct` $\to$ `estructura`, `int` $\to$ `entero`).
- **Medición:** Mide con alta precisión (`QueryPerformanceCounter`) el tiempo de carga del archivo dinámico y el tiempo de análisis léxico.
