#ifndef RED_H
#define RED_H

#include <string>
#include <map>
#include "Enrutador.h"

class Red {
private:
    // Contenedor STL global para almacenar todos los enrutadores que conforman la red
    std::map<std::string, Enrutador> enrutadores;

public:
    // Agrega un nuevo enrutador a la red si no existe
    void agregarEnrutador(const std::string& nombre);

    // Conecta dos enrutadores de forma bidireccional con un costo de enlace
    void conectar(const std::string& origen, const std::string& destino, int costo);

    // Imprime las tablas de todos los enrutadores de la red
    void mostrarRed() const;
};

#endif
