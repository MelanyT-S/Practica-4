#include <iostream>
#include "Red.h"
#include <iostream>

void mostrarMenu() {
    std::cout << "       SISTEMA DE GESTION DE ENRUTAMIENTO        \n";
    std::cout << " 1. Cargar red desde archivo \n";
    std::cout << " 2. Mostrar tablas de enrutamiento de toda la red\n";
    std::cout << " 3. Consultar camino y costo entre Origen y Destino\n";
    std::cout << " 4. Agregar o conectar un enlace \n";
    std::cout << " 5. Eliminar un enlace o enrutador \n";
    std::cout << " 6. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

int main() {
    Red miRed;
    int opcion;
    std::string archivo, origen, destino;
    int costo;

    do {
        mostrarMenu();
        std::cin >> opcion;

        switch (opcion) {
        case 1:
            std::cout << "Ingrese el nombre del archivo : ";
            std::cin >> archivo;
            if (miRed.cargarDesdeArchivo(archivo)) {
                std::cout << "  Red configurada y cargada exitosamente desde el archivo\n";
                miRed.calcularRutasMinimas(); // Calculo inicial de Dijkstra
            } else {
                std::cout << ">>> Error: No se pudo abrir el archivo.\n";
            }
            break;

        case 2:
            std::cout << "\n  MOSTRANDO TODAS LAS TABLAS DE ENRUTAMIENTO:\n";
            miRed.mostrarRedCompleta();
            break;

        case 3:
            std::cout << "Ingrese el enrutador de ORIGEN: ";
            std::cin >> origen;
            std::cout << "Ingrese el enrutador de DESTINO: ";
            std::cin >> destino;
            miRed.consultarCaminoEspecifico(origen, destino);
            break;

        case 4:
            std::cout << "Ingrese enrutador Origen: ";
            std::cin >> origen;
            std::cout << "Ingrese enrutador Destino: ";
            std::cin >> destino;
            std::cout << "Ingrese el costo del enlace: ";
            std::cin >> costo;
            miRed.conectar(origen, destino, costo);
            std::cout << ">>> Enlace agregado y rutas recalculadas automaticamente\n";
            break;

        case 5:
            std::cout << "Desea eliminar (1) Un Enlace o (2) Un Enrutador completo?: ";
            int subOpt;
            std::cin >> subOpt;
            if (subOpt == 1) {
                std::cout << "Ingrese Origen del enlace a desconectar: ";
                std::cin >> origen;
                std::cout << "Ingrese Destino del enlace a desconectar: ";
                std::cin >> destino;
                miRed.desconectar(origen, destino);
                std::cout << ">>> Enlace eliminado y red recalculada!\n";
            } else if (subOpt == 2) {
                std::cout << "Ingrese el nombre del enrutador a eliminar: ";
                std::cin >> origen;
                miRed.eliminarEnrutador(origen);
                std::cout << ">>> Enrutador eliminado de la red!\n";
            }
            break;

        case 6:
            std::cout << "Saliendo del programa... \n";
            break;

        default:
            std::cout << "Opcion invalida. Intente de nuevo.\n";
        }
    }
    while (opcion != 6);
}