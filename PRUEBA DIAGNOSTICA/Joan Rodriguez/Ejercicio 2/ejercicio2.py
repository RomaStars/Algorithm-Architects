import time

# genera coeficientes de (x+1)^n con el triangulo de pascal
def generar_pascal(n):
    fila_ant = [1]
    for i in range(1, n + 1):
        # reservar lista dinamica para el nivel actual
        fila_act = [1] * (i + 1)
        for j in range(1, i):
            fila_act[j] = fila_ant[j - 1] + fila_ant[j]
        fila_ant = fila_act
    return fila_ant

# arma la cadena del polinomio (x+1)^n
def formatear_polinomio(coefs, n):
    if n == 0:
        return "1"
    partes = []
    for i, c in enumerate(coefs):
        exp = n - i
        if exp == 0:
            partes.append(f"{c}")
        elif exp == 1:
            partes.append(f"{c}x" if c > 1 else "x")
        else:
            partes.append(f"{c}x^{exp}" if c > 1 else f"x^{exp}")
    return " + ".join(partes)

# muestra el calculo paso a paso de f(x) = (x+1)^n
def evaluar_paso_a_paso(coefs, n, x):
    print(f"\nevaluando f({x}) = ({x}+1)^{n} por pasos:")
    terminos_str = []
    valores = []
    
    for i, c in enumerate(coefs):
        exp = n - i
        pot = x ** exp
        val = c * pot
        valores.append(val)
        terminos_str.append(f"{c}*({x}^{exp})")
        print(f"  paso {i + 1}: coef {c} * ({x}^{exp} = {pot}) = {val}")

    print(f"\nsuma de terminos: f({x}) = " + " + ".join(terminos_str))
    print(f"f({x}) = " + " + ".join(map(str, valores)))
    print(f"resultado final: f({x}) = {sum(valores)}")


if __name__ == "__main__":
    # datos de prueba para demostracion (incisos a y b)
    n_prueba = 5
    x_prueba = 2

    coefs = generar_pascal(n_prueba)
    print(f"--- prueba para n = {n_prueba}, x = {x_prueba} ---")
    print(f"coeficientes (n={n_prueba}): {coefs}")
    print(f"(x+1)^{n_prueba} = {formatear_polinomio(coefs, n_prueba)}")
    evaluar_paso_a_paso(coefs, n_prueba, x_prueba)

    # medicion de tiempo para generar n = 100
    print("\n--- medicion de rendimiento para n = 100 ---")
    inicio = time.perf_counter()
    coefs_100 = generar_pascal(100)
    tiempo_100 = time.perf_counter() - inicio

    print(f"cantidad de coeficientes generados: {len(coefs_100)}")
    print(f"coeficiente central C(100,50): {coefs_100[50]}")
    print(f"tiempo en generar n=100 (python): {tiempo_100:.8f} segundos")