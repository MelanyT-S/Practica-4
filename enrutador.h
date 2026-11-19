#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>
#include <vector>

class Enrutador {
private:
    std::string nombre; // Identificador único del nodo
    std::map<std::string, int> vecinosDirectos; // Vecinos inmediatos y costo del enlace (STL map)
    std::map<std::string, int> tablaCostos;     // Costo mínimo optimizado a cualquier destino
    std::map<std::string, std::vector<std::string>> caminos; // Secuencia de nodos del camino óptimo

public:
    Enrutador(std::string _nombre);

    std::string getNombre() const;
    void agregarVecino(const std::string& vecino, int costo);
    void eliminarVecino(const std::string& vecino); // Permite eliminar enlaces dinámicamente

    const std::map<std::string, int>& getVecinosDirectos() const;

    // Actualiza la tabla global tras ejecutar Dijkstra
    void actualizarDestino(const std::string& destino, int costo, const std::vector<std::string>& camino);
    void limpiarTabla();
    void imprimirTablaEnrutamiento() const;
};

#endif