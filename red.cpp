#include "Red.h"

// Metodo para registrar enrutadores en el mapa general de la red
void Red::agregarEnrutador(const std::string& nombre) {
    if (enrutadores.find(nombre) == enrutadores.end()) {
        enrutadores.insert({nombre, Enrutador(nombre)});
    }
}

// Establece el enlace bidireccional entre dos nodos
void Red::conectar(const std::string& origen, const std::string& destino, int costo) {
    // Asegura que ambos nodos existan antes de enlazarlos
    agregarEnrutador(origen);
    agregarEnrutador(destino);

    // Añade el vecino de manera mutua (grafo no dirigido)
    enrutadores.at(origen).agregarVecino(destino, costo);
    enrutadores.at(destino).agregarVecino(origen, costo);
}

// Recorre la red mostrando la informacion local de cada equipo
void Red::mostrarRed() const {
    for (const auto& par : enrutadores) {
        par.second.imprimirTablaDirecta();
    }
}