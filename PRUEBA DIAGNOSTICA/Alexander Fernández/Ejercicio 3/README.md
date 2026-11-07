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
- En `traductor_c.c`, se utiliza `fseek()` y `ftell()` para determinar la longitud exacta del archivo fuente en bytes.
- Luego se reserva un bloque dinámico en el heap mediante `malloc(tamano + 1)`.
- La lectura se efectúa en un solo paso mediante `fread()`, garantizando la máxima eficiencia de E/S.
- El archivo se libera adecuadamente al finalizar el análisis con `free()`.

### 2.2. Autómata Léxico y Discriminación de Tokens
Un error común en sustituciones simples por cadenas (como `replace`) es generar falsos positivos:
- Alterar identificadores que contienen palabras clave (ej: `printf` no debe convertirse en `prsinoe` al buscar `if`).
- Alterar texto dentro de literales de cadena (ej: `"ingrese el valor if"` debe mantenerse inalterado).
- Alterar comentarios de código (ej: `// if contador` no debe modificarse).

El analizador léxico implementado en C opera como un escáner formal que clasifica:
1. **Comentarios de una línea (`// ... \n`):** Se copian literalmente sin traducir.
2. **Comentarios multilínea (`/* ... */`):** Se copian literalmente sin traducir.
3. **Cadenas de caracteres (`" ... "`):** Se reconocen secuencias de escape `\"` y se preserva el texto literal.
4. **Constantes de caracteres (`' ... '`):** Se reconocen secuencias de escape `\'` y se copian literalmente.
5. **Identificadores y Palabras Clave (`[a-zA-Z_][a-zA-Z0-9_]*`):** Se extrae el lexema completo y se consulta en la tabla de 37 palabras reservadas estándar de C. Si coincide, se incrementa el contador de frecuencia y se sustituye por su equivalente en español; de lo contrario, se mantiene el identificador original.
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
| `traductor_c.c` | Analizador léxico y traductor en C (ANSI/C99) con gestión de memoria dinámica. |
| `programa_prueba.c` | Código C de ejemplo con estructuras, funciones, comentarios y cadenas. |
| `programa_traducido_c.c` | Archivo C resultante con las palabras reservadas traducidas al español. |
| `resultado_traduccion_c.txt` | Informe estadístico de frecuencias y tiempos medidos con alta precisión. |
| `ejecutar.bat` | Script de compilación y ejecución automática en Windows. |
| `README.md` | Documentación técnica del ejercicio. |

---

## 5. Instrucciones de Compilación y Ejecución

### Compilación con GCC (MinGW / Clang):
```bash
gcc -O2 traductor_c.c -o traductor_c.exe
```

### Ejecución con el archivo de prueba por defecto:
```bash
traductor_c.exe programa_prueba.c programa_traducido_c.c
```

### Para traducir cualquier otro archivo fuente en C:
```bash
traductor_c.exe mi_archivo.c mi_archivo_traducido.c
```

O haciendo doble clic en el archivo `ejecutar.bat`.
