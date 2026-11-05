# Ejercicio 3: Analizador Léxico y Traductor de Palabras Reservadas en Lenguaje C

**Universidad Nacional Experimental de Guayana (UNEG)**  
**Coordinación de Ingeniería en Informática**  
**Lenguajes y Compiladores — Periodo 2026-II**  
**Estudiante:** Alexander Fernández  
**Profesor:** Msc. Félix Márquez  

---

## 1. Descripción del Problema
Para un programa escrito en lenguaje C, cargado en una memoria de forma dinámica:
1. Verificar si existen **palabras reservadas** en C.
2. Identificarlas mediante análisis léxico discriminativo (sin confundir identificadores compuestos, comentarios o cadenas de texto).
3. Traducirlas a su equivalente correspondiente en idioma español.

---

## 2. Fundamento Teórico y Diseño Léxico

### 2.1. Carga Dinámica en Memoria
De acuerdo con el requisito explícito de la prueba diagnóstica:
- **En C (`traductor_c.c`):** Se utiliza `fseek()` y `ftell()` para determinar la longitud exacta del archivo en bytes, y luego se reserva un bloque dinámico en el heap con `malloc(tamano + 1)`. La lectura se efectúa en un solo paso mediante `fread()`, garantizando la máxima eficiencia de E/S.
- **En Python (`traductor_c.py`):** El contenido se lee en un búfer dinámico en memoria, reportando su tamaño exacto en bytes y líneas.

### 2.2. Autómata Léxico y Discriminación de Tokens
Un error común en sustituciones simples por cadenas (como `replace`) es generar falsos positivos:
- Alterar identificadores que contienen palabras clave (ej: `printf` no debe convertirse en `prsinoe` al buscar `if`).
- Alterar texto dentro de literales de cadena (ej: `"ingrese el valor if"` debe mantenerse inalterado).
- Alterar comentarios de código (ej: `// if contador` no debe modificarse).

El analizador léxico implementado aquí opera como un escáner formal que clasifica:
1. **Comentarios de una línea (`// ... \n`):** Se copian literalmente.
2. **Comentarios multilínea (`/* ... */`):** Se copian literalmente.
3. **Cadenas de caracteres (`" ... "`):** Se reconocen secuencias de escape `\"` y se preserva el texto literal.
4. **Constantes de caracteres (`' ... '`):** Se copian literalmente.
5. **Identificadores y Palabras Clave (`[a-zA-Z_][a-zA-Z0-9_]*`):** Se extrae el lexema completo y se consulta en la tabla de 37 palabras reservadas de C. Si coincide, se incrementa el contador de frecuencia y se traduce; de lo contrario, se mantiene el identificador original.
6. **Operadores y delimitadores:** Se transfieren sin alteraciones.

---

## 3. Tabla de Traducción de Palabras Reservadas

| Palabra C | Traducción Español | Palabra C | Traducción Español |
| :--- | :--- | :--- | :--- |
| `auto` | `auto` | `inline` | `enlinea` |
| `break` | `interrumpir` | `int` | `entero` |
| `case` | `caso` | `long` | `largo` |
| `char` | `caracter` | `register` | `registro` |
| `const` | `constante` | `restrict` | `restringido` |
| `continue` | `continuar` | `return` | `retornar` |
| `default` | `defecto` | `short` | `corto` |
| `do` | `hacer` | `signed` | `con_signo` |
| `double` | `doble` | `sizeof` | `tamano_de` |
| `else` | `sino` | `static` | `estatico` |
| `enum` | `enumeracion` | `struct` | `estructura` |
| `extern` | `externo` | `switch` | `segun` |
| `float` | `flotante` | `typedef` | `definir_tipo` |
| `for` | `para` | `union` | `union` |
| `goto` | `ira` | `unsigned` | `sin_signo` |
| `if` | `si` | `void` | `vacio` |
| `volatile` | `volatil` | `while` | `mientras` |
| `_Bool` | `_Booleano` | `_Complex` | `_Complejo` |
| `_Imaginary`| `_Imaginario` | | |

---

## 4. Estructura de Archivos

| Archivo | Descripción |
| :--- | :--- |
| `traductor_c.py` | Analizador léxico y traductor en Python 3 puro. |
| `traductor_c.c` | Analizador léxico y traductor en C (ANSI/C99) con memoria dinámica. |
| `programa_prueba.c` | Código C de ejemplo con estructuras, funciones, comentarios y cadenas. |
| `programa_traducido_py.c` | Resultado generado por la versión Python. |
| `resultado_traduccion.txt` | Informe estadístico de frecuencias y tiempos de ejecución. |
| `ejecutar.bat` | Script de compilación y ejecución automática. |
| `README.md` | Documentación técnica del ejercicio. |

---

## 5. Instrucciones de Compilación y Ejecución

### En Python:
```bash
python traductor_c.py
```
*Para traducir un archivo C personalizado:*
```bash
python traductor_c.py mi_codigo.c
```

### En C (GCC / MinGW / Clang):
```bash
gcc -O2 traductor_c.c -o traductor_c.exe
traductor_c.exe programa_prueba.c programa_traducido_c.c
```

