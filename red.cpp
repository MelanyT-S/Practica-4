#include "Red.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <climits>

void Red::agregarEnrutador(const std::string& nombre) {
    if (enrutadores.find(nombre) == enrutadores.end()) {
        enrutadores.insert({nombre, Enrutador(nombre)}); // Insercion dinamica de nodo
    }
}

void Red::eliminarEnrutador(const std::string& nombre) {
    if (enrutadores.find(nombre) != enrutadores.end()) {
        // Limpiamos las referencias de este nodo en los demas enrutadores
        for (auto& par : enrutadores) {
            par.second.eliminarVecino(nombre);
        }
        enrutadores.erase(nombre); // Eliminacion del mapa global
        calcularRutasMinimas();     // Recalculo automatico de la red tras la baja
    }
}

void Red::conectar(const std::string& origen, const std::string& destino, int costo) {
    agregarEnrutador(origen);
    agregarEnrutador(destino);
    enrutadores.at(origen).agregarVecino(destino, costo); // Enlace bidireccional
    enrutadores.at(destino).agregarVecino(origen, costo);
    calcularRutasMinimas(); // Recalculo automatico de rutas al insertar enlace
}

void Red::desconectar(const std::string& origen, const std::string& destino) {
    if (enrutadores.find(origen) != enrutadores.end()) {
        enrutadores.at(origen).eliminarVecino(destino);
    }
    if (enrutadores.find(destino) != enrutadores.end()) {
        enrutadores.at(destino).eliminarVecino(origen);
    }
    calcularRutasMinimas(); // Recalculo automatico al eliminar enlace
}

bool Red::cargarDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) return false;

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;
        std::stringstream ss(linea);
        std::string origen, destino;
        int costo;
        if (ss >> origen >> destino >> costo) {
            conectar(origen, destino, costo); // Configuración inicial leyendo el .txt
        }
    }
    archivo.close();
    return true;
}

void Red::calcularRutasMinimas() {
    // Algoritmo Dijkstra centralizado: recalcula costos minimos y vectores de caminos
    for (auto& parOrigen : enrutadores) {
        std::string inicio = parOrigen.first;
        Enrutador& routerOrigen = parOrigen.second;
        routerOrigen.limpiarTabla();

        std::map<std::string, int> distancias;
        std::map<std::string, std::string> predecesores;
        std::priority_queue<std::pair<int, std::string>,
                            std::vector<std::pair<int, std::string>>,
                            std::greater<std::pair<int, std::string>>> pq;

        for (const auto& par : enrutadores) {
            distancias[par.first] = INT_MAX;
        }

        distancias[inicio] = 0;
        pq.push({0, inicio});

        while (!pq.empty()) {
            int costoActual = pq.top().first;
            std::string nodoActual = pq.top().second;
            pq.pop();

            if (costoActual > distancias[nodoActual]) continue;

            const auto& vecinos = enrutadores.at(nodoActual).getVecinosDirectos();
            for (const auto& vecPar : vecinos) {
                std::string vecino = vecPar.first;
                int costoEnlace = vecPar.second;

                if (distancias[nodoActual] + costoEnlace < distancias[vecino]) {
                    distancias[vecino] = distancias[nodoActual] + costoEnlace;
                    predecesores[vecino] = nodoActual;
                    pq.push({distancias[vecino], vecino});
                }
            }
        }

        // Construcción del vector con la ruta Optima para cada destino
        for (const auto& distPar : distancias) {
            std::string destino = distPar.first;
            int costoTotal = distPar.second;

            if (costoTotal != INT_MAX) {
                std::vector<std::string> camino;
                std::string actual = destino;
                while (actual != inicio) {
                    camino.insert(camino.begin(), actual);
                    actual = predecesores[actual];
                }
                camino.insert(camino.begin(), inicio);
                routerOrigen.actualizarDestino(destino, costoTotal, camino);
            }
        }
    }
}

void Red::mostrarRedCompleta() const {
    for (const auto& par : enrutadores) {
        par.second.imprimirTablaEnrutamiento();
    }
}
// Consulta de ruta y costo entre dos nodos específicos usando los contenedores STL
void Red::consultarCaminoEspecifico(const std::string& origen, const std::string& destino) const {
    if (enrutadores.find(origen) == enrutadores.end()) {
        std::cout << "Error: El enrutador de origen '" << origen << "' no existe en la red.\n";
        return;
    }

    // Obtenemos el enrutador origen
    const Enrutador& router = enrutadores.at(origen);

    // Imprimimos la consulta utilizando el contenedor vector almacenado en el enrutador
    std::cout << " Consulta de Camino: [" << origen << "] ---> [" << destino << "]\n";

    // Verificamos si existe ruta hacia ese destino llamando a un método o recorriendo
    std::cout << " Mostrando ruta optima calculada con contenedores STL:\n";
    router.imprimirTablaEnrutamiento(); // O puedes filtrar solo el destino si prefieres
}