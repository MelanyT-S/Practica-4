#include "Red.h"

int main() {
    Red miRed;

    // Ingresamos los valores de prueba de los enlaces directos (basado en el ejemplo de la guía)
    miRed.conectar("A", "B", 4);
    miRed.conectar("A", "C", 10);
    miRed.conectar("A", "D", 5);
    miRed.conectar("B", "C", 3);
    miRed.conectar("B", "D", 1);
    miRed.conectar("C", "D", 2);

    // Mostramos los resultados correspondientes
    miRed.mostrarRed();

    return 0;
}