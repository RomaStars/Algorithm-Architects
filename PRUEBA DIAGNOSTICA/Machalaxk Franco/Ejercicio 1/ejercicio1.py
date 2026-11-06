"""
============================================================================
 EJERCICIO 1 - PRUEBA DIAGNÓSTICA
 Lenguajes y Compiladores - UNEG - Periodo 2026-II
----------------------------------------------------------------------------
 RESUMEN DEL FUNCIONAMIENTO
----------------------------------------------------------------------------
 El programa valida una secuencia de movimientos de caballo sobre un
 tablero de ajedrez (filas 1..8, columnas a..h).

 REGLAS QUE SE VERIFICAN:
   1. Cada movimiento debe comenzar con la letra 'K' (Knight = caballo).
      Si comienza con otra letra, se reporta:
         "letra X no pertenece a un caballo".
   2. La casilla debe estar dentro del tablero: columna a..h, fila 1..8.
   3. El salto desde la posición actual debe ser en forma de L:
      (|dfila|, |dcol|) == (1,2) o (2,1).
   4. Si un movimiento falla, el programa se DETIENE y reporta el número
      de movimiento (1-based) donde ocurrió el error.

 COMPLEJIDAD: O(n) por secuencia, n = cantidad de movimientos.
============================================================================
"""

import time
from pathlib import Path

# ===========================================================================
# FUNCIÓN: analizar_casilla
# Convierte una casilla como "a2" o "Ka2" a su representación numérica.
# ===========================================================================
def analizar_casilla(s: str):
    if s is None: raise ValueError("posicion vacia")
    t = s.strip()
    
    if t[:1] in ("K", "k"): t = t[1:]
    if len(t) != 2: raise ValueError("notacion invalida")
    
    col = t[0].lower()
    fila = t[1]
    
    if col < "a" or col > "h" or fila < "1" or fila > "8": raise ValueError("fuera del tablero")
    
    return int(fila) - 1, ord(col) - ord("a")

# ===========================================================================
# FUNCIÓN: validar_movimiento
# Valida UN movimiento contra la posición actual.
# ===========================================================================
def validar_movimiento(actual, token: str):
    if not token: return False, None, "movimiento vacio"
    if token[0] != "K": return False, None, f"letra {token[0]} no pertenece a un caballo"
    
    try: siguiente = analizar_casilla(token)
    except ValueError: return False, None, "notacion de movimiento invalida"
    
    dfila = abs(siguiente[0] - actual[0])
    dcol = abs(siguiente[1] - actual[1])
    
    if not ((dfila == 1 and dcol == 2) or (dfila == 2 and dcol == 1)):
        return False, None, "no es un movimiento valido de caballo"
        
    return True, siguiente, ""

# ===========================================================================
# FUNCIÓN: validar_secuencia
# Recorre la cadena de movimientos. Se detiene en el primer error.
# ===========================================================================
def validar_secuencia(inicio, movimientos: str, n: int | None = None):
    tokens = movimientos.split()
    
    if n is not None:
        if len(tokens) < n: return False, len(tokens) + 1, "faltan movimientos"
        tokens = tokens[:n]
        
    actual = inicio
    for i, token in enumerate(tokens, start=1):
        es_valido, siguiente, razon = validar_movimiento(actual, token)
        if not es_valido:
            return False, i, razon
        actual = siguiente
        
    return True, 0, ""

# Lista COMPLETA de 500 movimientos suministrada en el PDF ACTUALIZADO.
LISTA_500 = """
Kb4 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2
Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8
Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5
Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5
Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6
Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6
Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1
Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3
Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7
Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4
Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1
Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4
Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5
Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2
Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4
Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4
Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6
Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3
Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5
Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7
Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1
Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5
Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4
"""

# ===========================================================================
# FUNCIÓN PRINCIPAL: main
# ===========================================================================
def main():
    ruta = Path("resultado_ej1_py.txt")
    lineas_reporte = []

    # -----------------------------------------------------------------
    # (1) EJECUCIÓN DE LOS 9 CASOS DE PRUEBA DEL ENUNCIADO
    # ---------------------------------------------------------------
    casos = [
        ("a1", 4,  "Kc2 Kd4 Kb3 Kc5"),
        ("a1", 4,  "Kc2 Kd4 Kb4 Kc5"),
        ("a2", 5,  "Kc3 Ke4 Kf6 Ke8 Kg7"),
        ("a2", 5,  "Kc8 Ke4 Kf6 Ke8 Kg7"),
        ("a8", 2,  "Kb6 Kd7"),
        ("a8", 2,  "Kb6 Kb7"),
        ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kb4"),
        ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4"),
        ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kh6 Kb4")
    ]

    lineas_reporte.append("======================================================================")
    lineas_reporte.append("VERIFICACION DE LOS CASOS DE PRUEBA DEL ENUNCIADO:")
    lineas_reporte.append("======================================================================\n")

    for i, (pos, n, movs) in enumerate(casos, start=1):
        inicio = analizar_casilla(pos)
        es_valido, fallo, razon = validar_secuencia(inicio, movs, n)
        
        if es_valido:
            res = "movimiento CORRECTO."
        elif "letra" in razon:
            res = f"INCORRECTO falla {razon}."
        else:
            res = f"INCORRECTO falla en el movimiento {fallo}."
            
        linea = f"Para Ak = {pos} n={n} y C={movs}\n  salida: {res}"
        print(f"Caso {i}: {res}")
        lineas_reporte.append(linea + "\n")

    # -----------------------------------------------------------------
    # (2) MEDICIÓN DE TIEMPO CON LOS 500 MOVIMIENTOS
    # ---------------------------------------------------------------
    inicio = analizar_casilla("a2")
    
    # Medición: 10 iteraciones de los 500 movimientos
    t0 = time.perf_counter()
    r2 = None
    for _ in range(10):
        r2 = validar_secuencia(inicio, LISTA_500, None)
    t1 = time.perf_counter()
    ms2 = (t1 - t0) * 1000.0

    lineas_reporte.append("\n======================================================================")
    lineas_reporte.append("REPORTE DE MEDICION DE TIEMPOS (10 iteraciones de los 500 movimientos):")
    lineas_reporte.append("======================================================================\n")
    
    lineas_reporte.append(f"- Estado final: movimiento {'CORRECTO' if r2[0] else 'INCORRECTO'}.")
    lineas_reporte.append(f"- Tiempo total (10 pasadas): {ms2:.4f} ms")
    lineas_reporte.append(f"- Tiempo promedio por pasada: {ms2/10.0:.4f} ms\n")

    # Escribir todo en el archivo
    texto_final = (
        "UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n"
        "PRUEBA DIAGNOSTICA - LENGUAJES Y COMPILADORES\n"
        "EJERCICIO 1: VERIFICADOR DE MOVIMIENTOS DE CABALLO (LENGUAJE PYTHON)\n"
        "======================================================================\n\n"
        + "\n".join(lineas_reporte)
    )
    
    ruta.write_text(texto_final, encoding="utf-8")
    print("\nEjecucion en Python finalizada. Revisar 'resultado_ej1_py.txt'")

if __name__ == "__main__":
    main()