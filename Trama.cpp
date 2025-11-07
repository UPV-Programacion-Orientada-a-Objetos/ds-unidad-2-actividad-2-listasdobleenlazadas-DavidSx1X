#include "Trama.h"
#include "ListaDeCarga.h" 
#include "RotorDeMapeo.h" 
#include <iostream> 

// --- Implementación de TramaLoad ---

void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    // 1. Preguntar al rotor por el mapeo del fragmento
    char decodificado = rotor->getMapeo(this->fragmento);
    
    // 2. Insertar el carácter decodificado en la lista de carga
    carga->insertarAlFinal(decodificado);

    // Feedback visual
    std::cout << " -> Procesando... -> Fragmento '" << this->fragmento 
              << "' decodificado como '" << decodificado << "'. Mensaje: ";
    carga->imprimirMensaje();
}


// --- Implementación de TramaMap ---

void TramaMap::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    // 1. Simplemente, rotar el rotor
    rotor->rotar(this->rotacion);

    // Feedback visual
    std::cout << " -> Procesando... -> ROTANDO ROTOR " 
              << (this->rotacion > 0 ? "+" : "") << this->rotacion 
              << ". (Ahora 'A' se mapea a '" << rotor->getMapeo('A') << "')";
}