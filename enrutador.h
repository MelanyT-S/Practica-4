#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>

class Enrutador {
private:
    std::string nombre; // Identificador del enrutador
    std::map<std::string, int> vecinos; // Contenedor STL para almacenar vecinos directos y su costo
    std::map<std::string, int> tablaCostos; // Tabla de costos locales (para la entrega 1 muestra los directos)

public:
    // Constructor para inicializar el enrutador con su nombre
    Enrutador(std::string _nombre);

    // Retorna el nombre del enrutador
    std::string getNombre() const;

    // Agrega un vecino directo y su respectivo costo usando la STL
    void agregarVecino(const std::string& vecino, int costo);

    // Muestra en consola la tabla de costos directos
    void imprimirTablaDirecta() const;
};

#endif