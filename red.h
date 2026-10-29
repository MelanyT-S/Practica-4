#ifndef RED_H
#define RED_H

#include <string>
#include <map>
#include "Enrutador.h"

class Red {
private:
    std::map<std::string, Enrutador> enrutadores; // Contenedor global de enrutadores de la red

public:
    // Inserción y eliminación dinámica de nodos y enlaces exigida por la guía
    void agregarEnrutador(const std::string& nombre);
    void eliminarEnrutador(const std::string& nombre);

    void conectar(const std::string& origen, const std::string& destino, int costo);
    void desconectar(const std::string& origen, const std::string& destino);

    bool cargarDesdeArchivo(const std::string& nombreArchivo); // Configuración inicial por .txt
    void calcularRutasMinimas(); // Algoritmo Dijkstra centralizado para recalcular red
    void mostrarRedCompleta() const;

    // Consultar ruta y costo entre un origen y un destino específico
    void consultarCaminoEspecifico(const std::string& origen, const std::string& destino) const;
};

#endif