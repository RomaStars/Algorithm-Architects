"""
============================================================================
 EJERCICIO 3 - PRUEBA DIAGNÓSTICA
 Lenguajes y Compiladores - UNEG - Periodo 2026-II
----------------------------------------------------------------------------
 Se carga un programa escrito en C y se recorre con un lexer simple que 
 respeta comentarios, cadenas, caracteres y directivas de preprocesador.
 
 Cada identificador se busca en una TABLA de palabras reservadas de C. 
 Si coincide, se reemplaza por su equivalente en español y se registra 
 el conteo en un reporte final.
============================================================================
"""

from pathlib import Path

# ===========================================================================
# TABLA DE PALABRAS RESERVADAS
# ===========================================================================
TABLA = {
    "_Alignas": "alinear_como", "_Alignof": "alineacion_de", "_Atomic": "atomico",
    "_Bool": "booleano", "_Complex": "complejo", "_Generic": "generico",
    "_Imaginary": "imaginario", "_Noreturn": "sin_retorno", "_Static_assert": "asercion_estatica",
    "_Thread_local": "hilo_local", "auto": "automatico", "break": "romper",
    "case": "caso", "char": "caracter", "const": "constante", "continue": "continuar",
    "default": "por_defecto", "do": "hacer", "double": "doble", "else": "sino",
    "enum": "enumeracion", "extern": "externo", "float": "flotante", "for": "para",
    "goto": "ir_a", "if": "si", "inline": "en_linea", "int": "entero",
    "long": "largo", "register": "registro", "restrict": "restringido", "return": "retornar",
    "short": "corto", "signed": "con_signo", "sizeof": "tamano_de", "static": "estatico",
    "struct": "estructura", "switch": "segun", "typedef": "tipo_def", "union": "union",
    "unsigned": "sin_signo", "void": "vacio", "volatile": "volatil", "while": "mientras",
}


def analizar_y_traducir(codigo: str) -> tuple[str, dict[str, int]]:
    salida = []
    conteos = {}
    i = 0
    n = len(codigo)

    while i < n:
        c = codigo[i]

        # Comentario de línea: // ...
        if c == "/" and i + 1 < n and codigo[i + 1] == "/":
            ini = i
            while i < n and codigo[i] != "\n": i += 1
            salida.append(codigo[ini:i])
            continue

        # Comentario de bloque: /* ... */
        if c == "/" and i + 1 < n and codigo[i + 1] == "*":
            ini = i
            i += 2
            while i + 1 < n and not (codigo[i] == "*" and codigo[i + 1] == "/"): i += 1
            if i + 1 < n: i += 2
            salida.append(codigo[ini:i])
            continue

        # Cadena: "..."
        if c == '"':
            ini = i
            i += 1
            while i < n:
                if codigo[i] == "\\" and i + 1 < n: i += 2; continue
                if codigo[i] == '"': i += 1; break
                i += 1
            salida.append(codigo[ini:i])
            continue

        # Carácter: '...'
        if c == "'":
            ini = i
            i += 1
            while i < n:
                if codigo[i] == "\\" and i + 1 < n: i += 2; continue
                if codigo[i] == "'": i += 1; break
                i += 1
            salida.append(codigo[ini:i])
            continue

        # Preprocesador
        if c == "#":
            ini = i
            while i < n and codigo[i] != "\n": i += 1
            salida.append(codigo[ini:i])
            continue

        # Identificador
        if c.isalpha() or c == "_":
            ini = i
            while i < n and (codigo[i].isalnum() or codigo[i] == "_"): i += 1
            palabra = codigo[ini:i]

            if palabra in TABLA:
                salida.append(TABLA[palabra])
                conteos[palabra] = conteos.get(palabra, 0) + 1
            else:
                salida.append(palabra)
            continue

        salida.append(c)
        i += 1

    return "".join(salida), conteos


def main() -> None:
    carpeta = Path(__file__).parent
    ruta_entrada = carpeta / "programa_ejemplo.c"
    ruta_traducido = carpeta / "programa_traducido_py.txt"
    ruta_reporte = carpeta / "resultado_ej3_py.txt"

    if not ruta_entrada.exists():
        print(f"Error: No se encontro '{ruta_entrada.name}'.")
        return

    codigo = ruta_entrada.read_text(encoding="utf-8")
    traducido, conteos = analizar_y_traducir(codigo)

    # Guardar archivo traducido
    ruta_traducido.write_text(traducido, encoding="utf-8")

    total = sum(conteos.values())

    # Generar reporte profesional
    with open(ruta_reporte, "w", encoding="utf-8") as f:
        f.write("UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n")
        f.write("PRUEBA DIAGNOSTICA - LENGUAJES Y COMPILADORES\n")
        f.write("EJERCICIO 3: ANALIZADOR LEXICO Y TRADUCCION (LENGUAJE PYTHON)\n")
        f.write("======================================================================\n\n")
        
        f.write("REPORTE DE ANALISIS DE PALABRAS RESERVADAS:\n")
        f.write(f"Programa analizado: {ruta_entrada.name}\n")
        f.write(f"Longitud del codigo: {len(codigo)} bytes\n")
        f.write(f"Total de ocurrencias encontradas: {total}\n\n")

        f.write("DETALLE DE PALABRAS TRADUCIDAS:\n")
        for palabra in sorted(conteos):
            f.write(f"  - {palabra:<12} -> {TABLA[palabra]:<15} ({conteos[palabra]} vez{'' if conteos[palabra] == 1 else 'es'})\n")
            
        f.write("\nEVIDENCIA DE TRADUCCION:\n")
        f.write(f"El codigo traducido se ha guardado exitosamente en '{ruta_traducido.name}'.\n")

    print(f"Ejecucion en Python finalizada. Revisar '{ruta_reporte.name}' y '{ruta_traducido.name}'.")


if __name__ == "__main__":
    main()