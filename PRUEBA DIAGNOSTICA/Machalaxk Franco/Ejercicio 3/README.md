# Ejercicio 3: Analizador Léxico y Traducción de Palabras Reservadas en C

**Universidad Nacional Experimental de Guayana (UNEG)**  
**Coordinación de Ingeniería en Informática**  
**Lenguajes y Compiladores — Periodo 2026-II**  
**Estudiante:** Mchalaxk Franco  
**Profesor:** Msc. Félix Márquez  

---

## 1. Descripción del Problema
Para un programa escrito en lenguaje C, cargado en memoria de forma dinámica, el programa debe:
1. **Verificar si existen palabras reservadas** de C dentro del código fuente.
2. **Traducirlas a su equivalente en español**.
3. Evitar falsos positivos (no traducir palabras que estén dentro de cadenas de texto o comentarios).
4. Generar dos archivos de salida: un **reporte de conteo** y el **programa traducido**.

---

## 2. Fundamento Teórico y Algorítmico

### 2.1. Análisis Léxico (Lexer)
A diferencia de una simple búsqueda de texto (`Ctrl + F`), este programa implementa un **autómata o analizador léxico** que recorre el código carácter por carácter. Para garantizar la precisión, el lexer implementa reglas de exclusión:
- Si encuentra `//`, ignora el resto de la línea.
- Si encuentra `/*`, ignora todo hasta cerrar con `*/`.
- Si encuentra comillas dobles `"..."` o simples `'...'`, procesa la cadena completa sin traducir su contenido.
- Si encuentra el símbolo `#`, ignora la directiva de preprocesador.
Solo cuando identifica un **identificador válido** (`[A-Za-z_][A-Za-z0-9_]*`), procede a buscar la palabra en la tabla de traducción.

### 2.2. Gestión de Memoria Dinámica
- **En C (`ejercicio3.c`):** El código fuente del archivo `.c` se carga en un búfer que crece dinámicamente usando `malloc()` y `realloc()`. Esto garantiza que el programa pueda analizar archivos de cualquier tamaño sin desbordar la memoria (stack overflow).
- **En Python (`ejercicio3.py`):** La lectura se realiza de forma nativa, aprovechando la gestión automática de memoria del intérprete.

### 2.3. Complejidad Computacional
- **Complejidad Temporal:** $O(L)$, donde $L$ es la longitud en caracteres del programa analizado. Se realiza un único recorrido lineal.
- **Complejidad Espacial:** $O(L)$ para almacenar el búfer del código en memoria.

---

## 3. Estructura de Archivos

| Archivo | Descripción |
| :--- | :--- |
| `programa_ejemplo.c` | Programa en C que sirve como entrada para ser analizado. |
| `ejercicio3.c` | Implementación del lexer y traductor en C (con memoria dinámica). |
| `ejercicio3.py` | Implementación del lexer y traductor en Python. |
| `resultado_ej3_c.txt` | Reporte generado por C con el conteo de palabras. |
| `resultado_ej3_py.txt` | Reporte generado por Python con el conteo de palabras. |
| `programa_traducido_c.txt` | Salida del código con las palabras ya traducidas (C). |
| `programa_traducido_py.txt` | Salida del código con las palabras ya traducidas (Python). |
| `README.md` | Documentación técnica y académica del ejercicio. |

---

---

## 4. Diccionario de Palabras Reservadas (Tabla de Traducción)

El programa cuenta con un mapeo de las 44 palabras reservadas del estándar de C (C89, C99 y C11). A continuación se presenta la tabla completa que utiliza el analizador léxico:

| Palabra Reservada (C) | Traducción (Español) | Categoría / Uso |
| :--- | :--- | :--- |
| `auto` | `automatico` | Almacenamiento |
| `break` | `romper` | Control de flujo |
| `case` | `caso` | Control de flujo |
| `char` | `caracter` | Tipo de dato |
| `const` | `constante` | Calificador |
| `continue` | `continuar` | Control de flujo |
| `default` | `por_defecto` | Control de flujo |
| `do` | `hacer` | Control de flujo |
| `double` | `doble` | Tipo de dato |
| `else` | `sino` | Control de flujo |
| `enum` | `enumeracion` | Estructura / Tipo |
| `extern` | `externo` | Almacenamiento |
| `float` | `flotante` | Tipo de dato |
| `for` | `para` | Control de flujo |
| `goto` | `ir_a` | Control de flujo |
| `if` | `si` | Control de flujo |
| `inline` | `en_linea` | Función / Optimización |
| `int` | `entero` | Tipo de dato |
| `long` | `largo` | Tipo de dato |
| `register` | `registro` | Almacenamiento |
| `restrict` | `restringido` | Calificador |
| `return` | `retornar` | Control de flujo |
| `short` | `corto` | Tipo de dato |
| `signed` | `con_signo` | Tipo de dato |
| `sizeof` | `tamano_de` | Operador |
| `static` | `estatico` | Almacenamiento |
| `struct` | `estructura` | Estructura / Tipo |
| `switch` | `segun` | Control de flujo |
| `typedef` | `tipo_def` | Estructura / Tipo |
| `union` | `union` | Estructura / Tipo |
| `unsigned` | `sin_signo` | Tipo de dato |
| `void` | `vacio` | Tipo de dato |
| `volatile` | `volatil` | Calificador |
| `while` | `mientras` | Control de flujo |
| `_Alignas` | `alinear_como` | C11 |
| `_Alignof` | `alineacion_de` | C11 |
| `_Atomic` | `atomico` | C11 |
| `_Bool` | `booleano` | C99 |
| `_Complex` | `complejo` | C99 |
| `_Generic` | `generico` | C11 |
| `_Imaginary` | `imaginario` | C99 |
| `_Noreturn` | `sin_retorno` | C11 |
| `_Static_assert` | `asercion_estatica` | C11 |
| `_Thread_local` | `hilo_local` | C11 |

## 5. Instrucciones de Compilación y Ejecución

### En Python:
```bash
python ejercicio3.py

```
### En C (GCC / MinGW / Clang):
```bash
gcc ejercicio3.c -O2 -o ejercicio3
./ejercicio3

```
## 6. Verificación del Funcionamiento (Traducción)

El programa analizó un código de prueba (`programa_ejemplo.c`) diseñado para incluir estructuras complejas (punteros, `typedef`, `struct`, `switch`). Ambos lenguajes detectaron y tradujeron exitosamente **25 ocurrencias**:

| Palabra Reservada (Inglés) | Traducción (Español) | Ocurrencias | Estado |
| :--- | :--- | :---: | :---: |
| `break` | `romper` | 3 | ✅ PASS |
| `case` | `caso` | 2 | ✅ PASS |
| `char` | `caracter` | 2 | ✅ PASS |
| `const` | `constante` | 1 | ✅ PASS |
| `default` | `por_defecto` | 1 | ✅ PASS |
| `if` | `si` | 1 | ✅ PASS |
| `int` | `entero` | 4 | ✅ PASS |
| `return` | `retornar` | 3 | ✅ PASS |
| `sizeof` | `tamano_de` | 1 | ✅ PASS |
| `struct` | `estructura` | 2 | ✅ PASS |
| `switch` | `segun` | 1 | ✅ PASS |
| `typedef` | `tipo_def` | 1 | ✅ PASS |
| `unsigned` | `sin_signo` | 1 | ✅ PASS |
| `void` | `vacio` | 1 | ✅ PASS |
| `while` | `mientras` | 1 | ✅ PASS |
| **Total** | | **25** | **✅ PASS** |

*Nota: Palabras como `printf` o `malloc` no fueron traducidas (por no ser reservadas), y el texto dentro de las comillas (`"lexer"`) se mantuvo intacto.*

--- 

## 7. Resultados del Análisis y Notas Técnicas

Los reportes completos con esta información se encuentran guardados automáticamente en los archivos `resultado_ej3_c.txt` y `resultado_ej3_py.txt`.

| Métrica | Implementación en C | Implementación en Python |
| :--- | :--- | :--- |
| **Programa analizado** | `programa_ejemplo.c` | `programa_ejemplo.c` |
| **Total de ocurrencias** | `25` | `25` |
| **Longitud detectada** | `1096 bytes` | `1047 bytes` |
