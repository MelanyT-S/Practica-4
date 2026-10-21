#include "Enrutador.h"
#include <iostream>

// Constructor de la clase
Enrutador::Enrutador(std::string _nombre) {
    nombre = _nombre;
    // El costo de un enrutador hacia si mismo siempre es 0
    tablaCostos[nombre] = 0;
}

std::string Enrutador::getNombre() const {
    return nombre;
}

// Metodo para registrar la conexion directa con otro enrutador
void Enrutador::agregarVecino(const std::string& vecino, int costo) {
    vecinos[vecino] = costo;
    tablaCostos[vecino] = costo; // tabla refleja los costos directos
}

// Metodo para imprimir los datos locales
void Enrutador::imprimirTablaDirecta() const {
    std::cout << " Tabla de costos directos del Enrutador: " << nombre << std::endl;
    for (const auto& par : tablaCostos) {
        std::cout << "Destino: " << par.first << " | Costo: " << par.second << std::endl;
    }
    std::cout << std::endl;
}