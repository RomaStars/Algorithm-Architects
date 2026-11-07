"""
Universidad Nacional Experimental de Guayana (UNEG)
Coordinación de Ingeniería en Informática - Lenguajes y Compiladores
Periodo lectivo: 2026-II - Prueba Diagnóstica
Estudiante: Alexander Fernández
Ejercicio 2: Generación de Polinomio (x+1)^n mediante Triángulo de Pascal y Evaluación Dinámica
Lenguaje: Python (Estándar, sin librerías externas)
"""

import os
import sys
import time

# Directorio base del ejercicio (asegura que los archivos se generen siempre aquí)
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
RUTA_RESULTADOS = os.path.join(BASE_DIR, "resultado_tiempos_python.txt")

def generar_triangulo_pascal(n):
    """
    Genera los coeficientes de la fila n del triángulo de Pascal utilizando memoria dinámica.
    Retorna una lista dinámica con los coeficientes [C(n, 0), C(n, 1), ..., C(n, n)].
    """
    if n < 0:
        raise ValueError("El exponente n debe ser un entero no negativo.")
    
    fila_actual = [1]
    for r in range(1, n + 1):
        siguiente_fila = [1] * (r + 1)
        for j in range(1, r):
            siguiente_fila[j] = fila_actual[j - 1] + fila_actual[j]
        fila_actual = siguiente_fila
        
    return fila_actual

def formatear_polinomio(coeficientes):
    """
    Construye la representación algebraica en cadena del polinomio generado.
    Ejemplo: [1, 3, 3, 1] -> 'x^3 + 3x^2 + 3x + 1'
    """
    n = len(coeficientes) - 1
    if n == 0:
        return "1"
    
    terminos = []
    for i, c in enumerate(coeficientes):
        potencia = n - i
        if c == 0:
            continue
        
        # Formatear el coeficiente y la variable x
        if potencia == 0:
            termino = f"{c}"
        elif potencia == 1:
            termino = f"{c}x" if c != 1 else "x"
        else:
            termino = f"{c}x^{potencia}" if c != 1 else f"x^{potencia}"
            
        terminos.append(termino)
        
    return " + ".join(terminos)

def evaluar_paso_a_paso(coeficientes, x):
    """
    Muestra detalladamente por pasos el cálculo de f(x) = (x+1)^n
    según el polinomio generado y sus coeficientes.
    """
    n = len(coeficientes) - 1
    print("\n" + "=" * 70)
    print(f"   EVALUACIÓN PASO A PASO: f({x}) para n = {n}")
    print("=" * 70)
    
    polinomio_str = formatear_polinomio(coeficientes)
    print(f"Polinomio generado: P(x) = {polinomio_str}\n")
    
    print("[PASO 1] Planteamiento de la función con coeficientes del binomio:")
    terminos_formula = []
    for i, c in enumerate(coeficientes):
        pot = n - i
        if pot > 1:
            terminos_formula.append(f"({c}) * x^{pot}")
        elif pot == 1:
            terminos_formula.append(f"({c}) * x")
        else:
            terminos_formula.append(f"({c})")
    print("  f(x) = " + " + ".join(terminos_formula))
    
    print(f"\n[PASO 2] Sustitución del valor dado x = {x}:")
    terminos_sust = []
    for i, c in enumerate(coeficientes):
        pot = n - i
        if pot > 1:
            terminos_sust.append(f"({c}) * ({x})^{pot}")
        elif pot == 1:
            terminos_sust.append(f"({c}) * ({x})")
        else:
            terminos_sust.append(f"({c}) * 1")
    print(f"  f({x}) = " + " + ".join(terminos_sust))
    
    print("\n[PASO 3] Cálculo individual de potencias:")
    potencias = []
    for i in range(n + 1):
        pot = n - i
        val_pot = x ** pot
        potencias.append(val_pot)
        print(f"  ({x})^{pot} = {val_pot}")
        
    print("\n[PASO 4] Multiplicación de cada coeficiente por su potencia correspondiente:")
    terminos_calculados = []
    for i, c in enumerate(coeficientes):
        pot = n - i
        val_term = c * potencias[i]
        terminos_calculados.append(val_term)
        print(f"  Término {i + 1} (x^{pot}): {c} * {potencias[i]} = {val_term}")
        
    print("\n[PASO 5] Suma algebraica acumulada:")
    suma_total = sum(terminos_calculados)
    cadena_suma = " + ".join(str(t) for t in terminos_calculados)
    print(f"  f({x}) = {cadena_suma}")
    print(f"  f({x}) = {suma_total}")
    
    print("\n[PASO 6] Verificación directa con la fórmula canónica f(x) = (x + 1)^n:")
    valor_directo = (x + 1) ** n
    print(f"  ({x} + 1)^{n} = ({x + 1})^{n} = {valor_directo}")
    
    if suma_total == valor_directo:
        print(f"\n  [✓] VERIFICACIÓN EXITOSA: {suma_total} == {valor_directo}")
    else:
        print(f"\n  [X] DISCREPANCIA DETECTADA: {suma_total} != {valor_directo}")
        
    return suma_total

def benchmark_n100(repeticiones=100):
    """
    Mide el tiempo de ejecución para generar los coeficientes de (x+1)^100.
    """
    # Calentamiento
    generar_triangulo_pascal(100)
    
    t0 = time.perf_counter()
    for _ in range(repeticiones):
        coeffs_100 = generar_triangulo_pascal(100)
    t1 = time.perf_counter()
    
    tiempo_total_s = t1 - t0
    tiempo_promedio_ms = (tiempo_total_s / repeticiones) * 1000.0
    return coeffs_100, tiempo_promedio_ms

def demostracion_guia():
    """Muestra los ejemplos del triángulo de Pascal dados en la guía oficial (n=0 a n=7)."""
    print("=" * 70)
    print("   UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)")
    print("   LENGUAJES Y COMPILADORES - PRUEBA DIAGNÓSTICA")
    print("   EJERCICIO 2: POLINOMIO (x+1)^n Y TRIÁNGULO DE PASCAL (PYTHON)")
    print("=" * 70)
    print("\n[+] GENERACIÓN DE POLINOMIOS DE LA GUÍA (n = 0 hasta 7):")
    for n in range(8):
        c = generar_triangulo_pascal(n)
        poly = formatear_polinomio(c)
        c_str = " ".join(str(v) for v in c)
        print(f" (n={n}): {c_str:<25} -> (x+1)^{n} = {poly}")

def main():
    demostracion_guia()
    
    # Ejemplo paso a paso para un valor representativo (ej: n = 4, x = 3)
    n_demo = 4
    x_demo = 3
    coeffs_demo = generar_triangulo_pascal(n_demo)
    evaluar_paso_a_paso(coeffs_demo, x_demo)
    
    # Benchmark n=100
    print("\n" + "=" * 70)
    print("[+] MEDICIÓN DE TIEMPO PARA n = 100:")
    coeffs_100, tiempo_ms = benchmark_n100(repeticiones=200)
    print(f" - Coeficientes generados para n=100: {len(coeffs_100)} coeficientes.")
    print(f" - Coeficiente central C(100, 50)   : {coeffs_100[50]}")
    print(f" - Tiempo promedio de generación    : {tiempo_ms:.4f} ms")
    
    # Guardar en archivo de resultados (sobreescribe si ya existe en la carpeta del ejercicio)
    with open(RUTA_RESULTADOS, "w", encoding="utf-8") as f:
        f.write("UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n")
        f.write("PRUEBA DIAGNÓSTICA - LENGUAJES Y COMPILADORES\n")
        f.write("ESTUDIANTE: Alexander Fernández\n")
        f.write("EJERCICIO 2: POLINOMIO (x+1)^n CON TRIÁNGULO DE PASCAL (PYTHON)\n")
        f.write("=" * 70 + "\n\n")
        f.write("1. MEDICIÓN DE TIEMPO PARA n = 100 EN PYTHON:\n")
        f.write(f"   - Tiempo promedio en Python: {tiempo_ms:.4f} ms (medido sobre 200 iteraciones)\n")
        f.write(f"   - Coeficiente central C(100, 50): {coeffs_100[50]}\n")
        f.write(f"   - Total de coeficientes generados: {len(coeffs_100)}\n\n")
        f.write("2. POLINOMIO GENERADO PARA n = 4:\n")
        f.write(f"   P(x) = {formatear_polinomio(coeffs_demo)}\n\n")
        f.write(f"3. EVALUACIÓN PASO A PASO PARA f({x_demo}) con n = {n_demo}:\n")
        f.write(f"   Resultado final = {(x_demo + 1) ** n_demo}\n")
        f.write(f"   Verificación: ({x_demo}+1)^{n_demo} = {x_demo+1}^{n_demo} = {(x_demo + 1) ** n_demo}\n")
        
    print(f"\n[✓] Archivo de resultados guardado/sobreescrito exitosamente en: '{RUTA_RESULTADOS}'.")

if __name__ == "__main__":
    if len(sys.argv) == 3:
        n_arg = int(sys.argv[1])
        x_arg = int(sys.argv[2])
        c = generar_triangulo_pascal(n_arg)
        evaluar_paso_a_paso(c, x_arg)
    else:
        main()

