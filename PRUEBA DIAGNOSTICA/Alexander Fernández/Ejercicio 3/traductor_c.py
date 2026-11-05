"""
Universidad Nacional Experimental de Guayana (UNEG)
Coordinación de Ingeniería en Informática - Lenguajes y Compiladores
Periodo lectivo: 2026-II - Prueba Diagnóstica
Estudiante: Alexander Fernández
Ejercicio 3: Analizador Léxico y Traductor de Palabras Reservadas de C a Español
Lenguaje: Python (Estándar, sin librerías externas)
"""

import sys
import os
import time

# Directorio base del ejercicio (asegura que los archivos se lean y generen siempre aquí)
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
RUTA_ENTRADA_DEFECTO = os.path.join(BASE_DIR, "programa_prueba.c")
RUTA_SALIDA_DEFECTO = os.path.join(BASE_DIR, "programa_traducido_py.c")
RUTA_REPORTE_DEFECTO = os.path.join(BASE_DIR, "resultado_traduccion_python.txt")

# Diccionario oficial de palabras reservadas del estándar C (ISO C99/C11/ANSI) y su traducción
DICCIONARIO_PALABRAS_RESERVADAS = {
    "auto": "auto",
    "break": "interrumpir",
    "case": "caso",
    "char": "caracter",
    "const": "constante",
    "continue": "continuar",
    "default": "defecto",
    "do": "hacer",
    "double": "doble",
    "else": "sino",
    "enum": "enumeracion",
    "extern": "externo",
    "float": "flotante",
    "for": "para",
    "goto": "ira",
    "if": "si",
    "inline": "enlinea",
    "int": "entero",
    "long": "largo",
    "register": "registro",
    "restrict": "restringido",
    "return": "retornar",
    "short": "corto",
    "signed": "con_signo",
    "sizeof": "tamano_de",
    "static": "estatico",
    "struct": "estructura",
    "switch": "segun",
    "typedef": "definir_tipo",
    "union": "union",
    "unsigned": "sin_signo",
    "void": "vacio",
    "volatile": "volatil",
    "while": "mientras",
    "_Bool": "_Booleano",
    "_Complex": "_Complejo",
    "_Imaginary": "_Imaginario"
}

def cargar_archivo_en_memoria(ruta_archivo):
    """
    Carga de forma dinámica el contenido completo del archivo en memoria principal.
    Retorna el búfer de texto y el tamaño en bytes.
    """
    if not os.path.exists(ruta_archivo):
        raise FileNotFoundError(f"No se encontró el archivo: {ruta_archivo}")
    
    with open(ruta_archivo, "r", encoding="utf-8", errors="replace") as f:
        contenido = f.read()
    
    tamano_bytes = len(contenido.encode("utf-8"))
    return contenido, tamano_bytes

def analizar_y_traducir_lexico(codigo_fuente):
    """
    Analizador léxico manual que recorre el búfer de código fuente:
    - Respeta cadenas de texto entre comillas ("...") y caracteres ('...').
    - Respeta comentarios de una línea (//...) y multilínea (/*...*/).
    - Identifica identificadores válidos y verifica si son palabras reservadas.
    - Traduce únicamente las palabras reservadas al español.
    """
    i = 0
    n = len(codigo_fuente)
    salida = []
    palabras_encontradas = {}
    
    while i < n:
        c = codigo_fuente[i]
        
        # 1. Comentarios de una línea: // ...
        if c == '/' and i + 1 < n and codigo_fuente[i + 1] == '/':
            inicio = i
            i += 2
            while i < n and codigo_fuente[i] != '\n':
                i += 1
            salida.append(codigo_fuente[inicio:i])
            continue
            
        # 2. Comentarios multilínea: /* ... */
        if c == '/' and i + 1 < n and codigo_fuente[i + 1] == '*':
            inicio = i
            i += 2
            while i + 1 < n and not (codigo_fuente[i] == '*' and codigo_fuente[i + 1] == '/'):
                i += 1
            if i + 1 < n:
                i += 2
            else:
                i = n
            salida.append(codigo_fuente[inicio:i])
            continue
            
        # 3. Cadenas de texto: " ... "
        if c == '"':
            inicio = i
            i += 1
            while i < n:
                if codigo_fuente[i] == '\\' and i + 1 < n:
                    i += 2
                elif codigo_fuente[i] == '"':
                    i += 1
                    break
                else:
                    i += 1
            salida.append(codigo_fuente[inicio:i])
            continue
            
        # 4. Constantes de caracteres: ' ... '
        if c == "'":
            inicio = i
            i += 1
            while i < n:
                if codigo_fuente[i] == '\\' and i + 1 < n:
                    i += 2
                elif codigo_fuente[i] == "'":
                    i += 1
                    break
                else:
                    i += 1
            salida.append(codigo_fuente[inicio:i])
            continue
            
        # 5. Identificadores y Palabras Reservadas: [a-zA-Z_][a-zA-Z0-9_]*
        if c.isalpha() or c == '_':
            inicio = i
            while i < n and (codigo_fuente[i].isalnum() or codigo_fuente[i] == '_'):
                i += 1
            token = codigo_fuente[inicio:i]
            
            # Verificación de palabra reservada
            if token in DICCIONARIO_PALABRAS_RESERVADAS:
                palabras_encontradas[token] = palabras_encontradas.get(token, 0) + 1
                traduccion = DICCIONARIO_PALABRAS_RESERVADAS[token]
                salida.append(traduccion)
            else:
                salida.append(token)
            continue
            
        # 6. Cualquier otro carácter (operadores, delimitadores, espacios, saltos)
        salida.append(c)
        i += 1
        
    codigo_traducido = "".join(salida)
    return codigo_traducido, palabras_encontradas

def procesar_programa(ruta_entrada=None, ruta_salida=None):
    if ruta_entrada is None:
        ruta_entrada = RUTA_ENTRADA_DEFECTO
    elif not os.path.isabs(ruta_entrada) and not os.path.exists(ruta_entrada):
        # Si se pasa una ruta relativa que está dentro de la carpeta del ejercicio
        posible_ruta = os.path.join(BASE_DIR, ruta_entrada)
        if os.path.exists(posible_ruta):
            ruta_entrada = posible_ruta

    if ruta_salida is None:
        ruta_salida = RUTA_SALIDA_DEFECTO
    elif not os.path.isabs(ruta_salida):
        ruta_salida = os.path.join(BASE_DIR, ruta_salida)

    ruta_reporte = RUTA_REPORTE_DEFECTO

    print("=" * 70)
    print("   UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)")
    print("   LENGUAJES Y COMPILADORES - PRUEBA DIAGNÓSTICA")
    print("   EJERCICIO 3: ANALIZADOR Y TRADUCTOR DE PALABRAS RESERVADAS EN C")
    print("=" * 70)
    print(f"\n[+] Cargando archivo dinámicamente en memoria: '{ruta_entrada}'...")
    
    t0 = time.perf_counter()
    contenido, tamano_bytes = cargar_archivo_en_memoria(ruta_entrada)
    t_carga = time.perf_counter() - t0
    
    print(f" [✓] Archivo cargado con éxito. Tamaño en memoria: {tamano_bytes} bytes ({len(contenido.splitlines())} líneas).")
    
    print("\n[+] Ejecutando escaneo léxico y traducción...")
    t1 = time.perf_counter()
    traducido, conteo = analizar_y_traducir_lexico(contenido)
    t_analisis = time.perf_counter() - t1
    
    total_palabras_encontradas = sum(conteo.values())
    total_unicas = len(conteo)
    
    print(f" [✓] Análisis completado en {t_analisis * 1000:.4f} ms.")
    print(f"     - Total de apariciones de palabras reservadas : {total_palabras_encontradas}")
    print(f"     - Total de palabras reservadas únicas       : {total_unicas}")
    
    print("\n[+] DETALLE DE PALABRAS RESERVADAS IDENTIFICADAS Y TRADUCIDAS:")
    print("-" * 70)
    print(f"{'#':<4} {'Palabra C':<15} {'Traducción Español':<20} {'Frecuencia':<12}")
    print("-" * 70)
    for idx, (kw, cant) in enumerate(sorted(conteo.items(), key=lambda x: (-x[1], x[0])), 1):
        trad = DICCIONARIO_PALABRAS_RESERVADAS[kw]
        print(f"{idx:<4} {kw:<15} {trad:<20} {cant:<12}")
    print("-" * 70)
    
    # Guardar archivo traducido (sobreescribe si existe)
    with open(ruta_salida, "w", encoding="utf-8") as f:
        f.write(traducido)
    print(f"\n[✓] Código traducido guardado/sobreescrito en: '{ruta_salida}'")
    
    # Guardar informe de resultados (sobreescribe si existe)
    with open(ruta_reporte, "w", encoding="utf-8") as f:
        f.write("UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n")
        f.write("PRUEBA DIAGNÓSTICA - LENGUAJES Y COMPILADORES\n")
        f.write("ESTUDIANTE: Alexander Fernández\n")
        f.write("EJERCICIO 3: ANALIZADOR Y TRADUCTOR DE PALABRAS RESERVADAS EN C\n")
        f.write("=" * 70 + "\n\n")
        f.write(f"Archivo analizado : {ruta_entrada}\n")
        f.write(f"Tamaño dinámico   : {tamano_bytes} bytes\n")
        f.write(f"Tiempo de carga   : {t_carga * 1000:.4f} ms\n")
        f.write(f"Tiempo de análisis: {t_analisis * 1000:.4f} ms\n\n")
        f.write("RESUMEN DE PALABRAS RESERVADAS ENCONTRADAS:\n")
        f.write(f"- Palabras distintas encontradas: {total_unicas}\n")
        f.write(f"- Total de ocurrencias           : {total_palabras_encontradas}\n\n")
        f.write(f"{'#':<4} {'Palabra C':<15} {'Traducción Español':<20} {'Frecuencia':<12}\n")
        f.write("-" * 60 + "\n")
        for idx, (kw, cant) in enumerate(sorted(conteo.items(), key=lambda x: (-x[1], x[0])), 1):
            trad = DICCIONARIO_PALABRAS_RESERVADAS[kw]
            f.write(f"{idx:<4} {kw:<15} {trad:<20} {cant:<12}\n")
            
    print(f"[✓] Reporte guardado/sobreescrito en: '{ruta_reporte}'")

if __name__ == "__main__":
    if len(sys.argv) >= 2:
        procesar_programa(sys.argv[1])
    else:
        procesar_programa()

