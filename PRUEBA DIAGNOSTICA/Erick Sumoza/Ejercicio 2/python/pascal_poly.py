import time

def generate_pascal_coefficients(n: int) -> list[int]:
    """Genera los coeficientes del polinomio (x + 1)^n usando el Triángulo de Pascal."""
    if n < 0:
        raise ValueError("El exponente n debe ser no negativo.")
    
    row = [1]
    for _ in range(n):
        row = [1] + [row[j] + row[j + 1] for j in range(len(row) - 1)] + [1]
    
    return row

def format_polynomial(n: int, coeffs: list[int]) -> str:
    """Retorna la representación textual del polinomio f(x) = (x + 1)^n."""
    terms = []
    for i, coeff in enumerate(coeffs):
        power = n - i
        if power == 0:
            terms.append(f"{coeff}")
        elif power == 1:
            terms.append(f"x" if coeff == 1 else f"{coeff}x")
        else:
            terms.append(f"x^{power}" if coeff == 1 else f"{coeff}x^{power}")
    return f"f(x) = (x + 1)^{n} = " + " + ".join(terms)

def evaluate_polynomial_step_by_step(n: int, coeffs: list[int], x: float) -> float:
    """Evalúa el polinomio paso a paso imprimiendo el detalle de los cálculos."""
    print(f"\n--- Evaluacion paso a paso para x = {x} ---")
    total_sum = 0.0

    for i, coeff in enumerate(coeffs):
        power = n - i
        power_val = x ** power
        term_val = coeff * power_val
        total_sum += term_val
        print(f"Término {i + 1}: {coeff} * ({x})^{power} = {coeff} * {power_val:.4f} = {term_val:.4f}")

    direct_val = (x + 1.0) ** n
    print("-" * 40)
    print(f"Suma por polinomio  : {total_sum:.4f}")
    print(f"Verificación (x+1)^n: {direct_val:.4f}")
    
    return total_sum

def run_benchmark_python(n: int, repetitions: int, filename: str) -> None:
    """Mide el tiempo empleado, muestra los resultados y exporta un archivo de texto."""
    print(f"\n=== BENCHMARK PYTHON (n = {n}, {repetitions} repeticiones) ===")
    
    start_time = time.perf_counter()
    for _ in range(repetitions):
        _ = generate_pascal_coefficients(n)
    end_time = time.perf_counter()

    total_seconds = end_time - start_time
    avg_seconds = total_seconds / repetitions
    avg_ms = avg_seconds * 1000.0

    print(f"Tiempo total ({repetitions} ejecuciones): {total_seconds:.6f} segundos")
    print(f"Tiempo promedio por ejecución: {avg_seconds:.8f} segundos ({avg_ms:.6f} ms)")

    # Guardar resultados en un archivo de texto
    with open(filename, "w", encoding="utf-8") as f:
        f.write("===================================================\n")
        f.write("  RESULTADOS DE EJECUCION Y BENCHMARK - PYTHON\n")
        f.write("===================================================\n")
        f.write(f"Parametro n evaluado: {n}\n")
        f.write(f"Repeticiones de prueba: {repetitions}\n")
        f.write(f"Tiempo total: {total_seconds:.6f} segundos\n")
        f.write(f"Tiempo promedio: {avg_seconds:.8f} segundos ({avg_ms:.6f} ms)\n")
        f.write("Estado: Ejecucion exitosa con listas dinamicas.\n")
    
    print(f"Resultados guardados exitosamente en '{filename}'")