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

El proyecto está organizado estrictamente en tres carpetas según los lineamientos de la evaluación:

```
PRUEBA DIAGNOSTICA/Alexander Fernández/
│
├── ENLACE_DEFENSA.txt                # Enlace al video de defensa en Google Drive
├── README.md                          # Documentación general del estudiante
│
├── Ejercicio 1/                       # Verificación de Movimientos de Caballo en Ajedrez
│   ├── caballo.py                     # Implementación en Python 3 estándar
│   ├── caballo.c                      # Implementación en C estándar (ANSI/C99)
│   ├── resultado_tiempos_python.txt   # Resultados y mediciones de tiempo en Python
│   ├── resultado_tiempos_c.txt        # Resultados y mediciones de tiempo en C
│   ├── ejecutar.bat                   # Script de compilación y ejecución automática
│   └── README.md                      # Explicación teórica y complejidad O(n)
│
├── Ejercicio 2/                       # Polinomio (x+1)^n con Triángulo de Pascal y Memoria Dinámica
│   ├── pascal_polinomio.py            # Implementación en Python 3 estándar
│   ├── pascal_polinomio.c             # Implementación en C (ANSI/C99) con BigInt dinámico
│   ├── resultado_tiempos_python.txt   # Tiempos para n=100 y evaluación en Python
│   ├── resultado_tiempos_c.txt        # Tiempos para n=100 y evaluación en C
│   ├── ejecutar.bat                   # Script de compilación y ejecución automática
│   └── README.md                      # Explicación matemática y paso a paso
│
└── Ejercicio 3/                       # Analizador Léxico y Traductor de Palabras Reservadas en C
    ├── traductor_c.py                 # Analizador léxico y traductor en Python 3
    ├── traductor_c.c                  # Analizador léxico y traductor en C en memoria dinámica
    ├── programa_prueba.c              # Código C de prueba con funciones, structs y strings
    ├── programa_traducido_py.c        # Código resultante traducido por Python
    ├── programa_traducido_c.c         # Código resultante traducido por C
    ├── resultado_traduccion_python.txt# Reporte de análisis y frecuencias en Python
    ├── resultado_traduccion_c.txt     # Reporte de análisis y frecuencias en C
    ├── ejecutar.bat                   # Script de compilación y ejecución automática
    └── README.md                      # Documentación del autómata léxico
```

---

## Resumen de los Ejercicios Implementados

### 1. Ejercicio 1: Verificador de Movimientos de Caballo
- **Propósito:** Valida si una secuencia $C$ de saltos de caballo en notación ajedrecística (`Kc2`, `Kd4`, etc.) es legal partiendo de una casilla inicial $A_k$.
- **Lógica:** Implementa la distancia métrica del caballo $|\Delta x| \cdot |\Delta y| = 2$ en el tablero $8 \times 8$. Se detiene en cortocircuito al primer error y valida el prefijo `K` (reportando si otra letra como `Q` aparece).
- **Medición de Tiempos:** Evalúa para $n=100$ y realiza 10 repeticiones continuas sobre la secuencia provista en la guía académica.

### 2. Ejercicio 2: Generación de Polinomio $(x+1)^n$ con Triángulo de Pascal
- **Propósito:** Genera algebraicamente los coeficientes de $(x+1)^n$ usando memoria dinámica y muestra la evaluación detallada paso a paso de $f(x)$ para un valor $x$ dado.
- **Memoria Dinámica & BigInt:** En C, se implementó aritmética de enteros gigantes con cadenas dinámicas (`malloc`/`free`) para evitar desbordamientos de 64 bits en coeficientes que alcanzan el orden de $10^{29}$ para $n=100$.
- **Benchmark:** Comparación del tiempo de cálculo de la fila $n=100$ en Python ($\approx 0.27\text{ ms}$) frente a C.

### 3. Ejercicio 3: Analizador Léxico y Traductor de Palabras Reservadas
- **Propósito:** Carga dinámicamente un archivo fuente en lenguaje C en memoria (`malloc`/`fread`) e identifica palabras reservadas de la norma C99/C11/ANSI mediante un analizador léxico que ignora cadenas literales (`"..."`) y comentarios (`//...`, `/*...*/`).
- **Traducción:** Sustituye las 37 palabras reservadas de C por su contraparte en español (ej. `if` $\to$ `si`, `while` $\to$ `mientras`, `return` $\to$ `retornar`), produciendo un código fuente traducido e informes de frecuencias.

---

## Cómo Ejecutar los Proyectos
Todos los ejercicios están construidos con las **bibliotecas estándar nativas** de C y Python, **sin dependencias externas ni herramientas de terceros**:

- Para ejecutar cualquiera de las soluciones en Python:
  ```bash
  cd "Ejercicio 1" && python caballo.py
  cd "../Ejercicio 2" && python pascal_polinomio.py
  cd "../Ejercicio 3" && python traductor_c.py
  ```
- Para compilar y ejecutar en C:
  ```bash
  gcc -O2 caballo.c -o caballo.exe && caballo.exe
  gcc -O2 pascal_polinomio.c -o pascal_polinomio.exe && pascal_polinomio.exe
  gcc -O2 traductor_c.c -o traductor_c.exe && traductor_c.exe
  ```
- O simplemente ejecutar el archivo `ejecutar.bat` presente en cada una de las tres carpetas.

