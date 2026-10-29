#include "Enrutador.h"
#include <iostream>

Enrutador::Enrutador(std::string _nombre) : nombre(_nombre) {
    tablaCostos[nombre] = 0;
    caminos[nombre] = {nombre};
}

std::string Enrutador::getNombre() const { return nombre; }

void Enrutador::agregarVecino(const std::string& vecino, int costo) {
    vecinosDirectos[vecino] = costo; // Inserta o actualiza un vecino directo en O(log N) usando STL map
}

void Enrutador::eliminarVecino(const std::string& vecino) {
    vecinosDirectos.erase(vecino); // Elimina el enlace físico directo
    tablaCostos.erase(vecino);
    caminos.erase(vecino);
}

const std::map<std::string, int>& Enrutador::getVecinosDirectos() const {
    return vecinosDirectos;
}

void Enrutador::actualizarDestino(const std::string& destino, int costo, const std::vector<std::string>& camino) {
    tablaCostos[destino] = costo;
    caminos[destino] = camino; // Almacena el vector con la ruta completa
}

void Enrutador::limpiarTabla() {
    tablaCostos.clear();
    caminos.clear();
    tablaCostos[nombre] = 0;
    caminos[nombre] = {nombre};
}

void Enrutador::imprimirTablaEnrutamiento() const {
    std::cout << "--- Tabla de Enrutamiento del Nodo: " << nombre << " ---\n";
    std::cout << "Destino\tCosto\tCamino Óptimo\n";
    auto itCamino = caminos.begin();
    for (const auto& par : tablaCostos) {
        std::cout << "  " << par.first << "\t  " << par.second << "\t";
        if (itCamino != caminos.end()) {
            const auto& ruta = itCamino->second;
            for (size_t i = 0; i < ruta.size(); ++i) {
                std::cout << ruta[i] << (i + 1 < ruta.size() ? " -> " : "");
            }
        }
        std::cout << "\n";
        ++itCamino;
    }
    std::cout << "----------------------------------------------\n\n";
}