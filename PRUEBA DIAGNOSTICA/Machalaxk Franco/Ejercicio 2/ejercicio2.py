"""
============================================================================
 EJERCICIO 2 - PRUEBA DIAGNÓSTICA
 Lenguajes y Compiladores - UNEG - Periodo 2026-II
----------------------------------------------------------------------------
 Dado n >= 0 entero:
   a) Genera los coeficientes del polinomio (x+1)^n usando el
      TRIÁNGULO DE PASCAL, y muestra el polinomio resultante.
   b) Con esos coeficientes c_0..c_n, evalúa f(x) = sum c_i * x^i
      mostrando PASO A PASO cada término y la suma total.

 NOTAS:
   - En Python los enteros son de precisión arbitraria nativa, así
     que n=100 (coeficientes de hasta ~30 dígitos) se maneja sin
     librerías extra.
   - En C se implementa un EnteroGrande dinámico.
============================================================================
"""

import time
from pathlib import Path

# ===========================================================================
# FUNCIÓN: construir_fila_pascal
# ===========================================================================
def construir_fila_pascal(n: int) -> list[int]:
    fila = [0] * (n + 1)
    fila[0] = 1
    for k in range(1, n + 1):
        for j in range(k, 0, -1):
            fila[j] = fila[j] + fila[j - 1]
    return fila

# ===========================================================================
# FUNCIÓN: formatear_polinomio
# ===========================================================================
def formatear_polinomio(coeficientes: list[int]) -> str:
    n = len(coeficientes) - 1
    partes = []
    for i in range(n, -1, -1):
        coef = coeficientes[i]
        if coef == 0:
            continue
        if i == 0:
            partes.append(f"{coef}")
        elif i == 1:
            partes.append("x" if coef == 1 else f"{coef}x")
        else:
            partes.append(f"x^{i}" if coef == 1 else f"{coef}x^{i}")
    return " + ".join(partes) if partes else "0"

# ===========================================================================
# FUNCIÓN: evaluar_paso_a_paso
# ===========================================================================
def evaluar_paso_a_paso(archivo, coeficientes: list[int], x: int) -> None:
    n = len(coeficientes) - 1
    total = 0
    potencia = 1

    for i in range(n + 1):
        termino = coeficientes[i] * potencia
        total += termino
        archivo.write(f"Paso {i}: c_{i} * x^{i} = {coeficientes[i]} * {potencia} = {termino}\n")
        if i < n:
            potencia *= x

    archivo.write(f"f({x}) = {total}\n")

# ===========================================================================
# FUNCIÓN PRINCIPAL: main
# ===========================================================================
def main() -> None:
    ruta_reporte = Path("resultado_ej2_py.txt")
    
    with open(ruta_reporte, "w", encoding="utf-8") as archivo:
        # Encabezado del reporte
        archivo.write("UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n")
        archivo.write("PRUEBA DIAGNOSTICA - LENGUAJES Y COMPILADORES\n")
        archivo.write("EJERCICIO 2: POLINOMIO (X+1)^N Y EVALUACION (LENGUAJE PYTHON)\n")
        archivo.write("======================================================================\n\n")

        # Demostración con n=5 y x=2
        n_demo = 5
        x_demo = 2
        
        archivo.write(f"RESULTADO DE LA DEMOSTRACION (n={n_demo}, x={x_demo}):\n\n")
        coef_demo = construir_fila_pascal(n_demo)
        
        archivo.write("a) Polinomio generado:\n")
        archivo.write(f"(x+1)^{n_demo} = {formatear_polinomio(coef_demo)}\n")
        archivo.write(f"Coeficientes (Pascal): {' '.join(str(c) for c in coef_demo)}\n\n")
        
        archivo.write(f"b) Evaluacion paso a paso para x = {x_demo}:\n")
        evaluar_paso_a_paso(archivo, coef_demo, x_demo)

        # Medición n=100
        archivo.write("\n======================================================================\n")
        archivo.write("REPORTE DE MEDICION DE TIEMPOS DE EJECUCION:\n")
        archivo.write("Generacion del polinomio para n = 100\n")
        archivo.write("Repeticiones: 100\n\n")

        inicio = time.perf_counter()
        for _ in range(100):
            _ = construir_fila_pascal(100)
        fin = time.perf_counter()

        total_ms = (fin - inicio) * 1000.0
        promedio_ms = total_ms / 100.0

        archivo.write(f"Tiempo total (Python)    : {total_ms:.6f} ms\n")
        archivo.write(f"Tiempo promedio (Python) : {promedio_ms:.6f} ms\n")

    print("Ejecucion en Python finalizada. Revisar 'resultado_ej2_py.txt'")

if __name__ == "__main__":
    main()