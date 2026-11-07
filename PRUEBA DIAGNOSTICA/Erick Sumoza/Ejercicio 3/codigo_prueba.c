// Programa de prueba en C

int main(void) {
    int contador = 0;
    float suma = 0.0;
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            contador++;
        } else {
            continue;
        }
    }
    while (contador > 0) {
        contador--;
        break;
    }
    return 0;
}
