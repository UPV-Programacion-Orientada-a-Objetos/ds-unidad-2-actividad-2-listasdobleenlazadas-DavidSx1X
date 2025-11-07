#include <iostream>
#include <cstring> // Para strtok, strcpy, strcmp
#include <cstdlib> // Para atoi

#include "Trama.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include "Serial.h" // <-- Nuestra clase de conexión

/**
 * @brief Parsea una línea de texto del "serial" e instancia el objeto Trama correcto.
 *
 * Utiliza funciones de C-style (strtok, atoi) como se requiere,
 * evitando std::string.
 *
 * @param buffer Un buffer de caracteres *modificable* que contiene la línea (ej. "L,G" o "M,-2").
 * ¡Importante! strtok modifica el buffer.
 * @return Un puntero TramaBase* a un nuevo objeto (TramaLoad o TramaMap).
 * El llamador es responsable de hacer "delete" a este puntero.
 * Retorna NULL si la trama es inválida.
 */
TramaBase* parsearTrama(char* buffer) {
    // 1. Obtener el tipo (L o M)
    // strtok divide la cadena en "tokens" usando el delimitador ","
    char* tipo = strtok(buffer, ",");
    if (tipo == NULL) return NULL; // Trama mal formada

    // 2. Obtener el valor (G, Space, 5, -2)
    char* valor_str = strtok(NULL, "\n"); // Tomar el resto de la línea
    if (valor_str == NULL) return NULL; // Trama mal formada

    TramaBase* tramaGenerada = NULL;

    // 3. Instanciar el objeto correcto basado en el tipo
    if (strcmp(tipo, "L") == 0) {
        // Es una TramaLoad
        char dato_carga;
        
        // Manejar el caso especial "Space"
        if (strcmp(valor_str, "Space") == 0) {
            dato_carga = ' ';
        } else {
            // Tomar el primer carácter del valor
            dato_carga = valor_str[0]; 
        }
        
        tramaGenerada = new TramaLoad(dato_carga);

    } else if (strcmp(tipo, "M") == 0) {
        // Es una TramaMap
        // Convertir el string de valor (ej. "-2") a un entero
        int dato_mapa = atoi(valor_str);
        
        tramaGenerada = new TramaMap(dato_mapa);
    }
    
    // Si el tipo no fue ni 'L' ni 'M', se retornará NULL

    return tramaGenerada;
}


int main() {
    
    // 1. Inicialización de estructuras
    ListaDeCarga miListaDeCarga;
    RotorDeMapeo miRotorDeMapeo;
    
    // 2. Inicialización del Puerto Serial
    Serial miPuertoSerial;
    
    // ¡Aquí pones tu puerto! El "9600" debe coincidir
    // con el Serial.begin(9600) de tu Arduino.
    if (!miPuertoSerial.connect("COM8", 9600)) {
        std::cerr << "Fallo al conectar con el Arduino. Verifique el puerto COM8." << std::endl;
        return 1; // Salir con error
    }

    std::cout << "\nIniciando Decodificador PRT-7 (Modo Real)." << std::endl;
    std::cout << "Conectado a COM8. Esperando tramas..." << std::endl << std::endl;

    // Buffer para leer las líneas
    char buffer[100];

    // 3. Bucle de Procesamiento (Real)
    // El bucle se ejecutará mientras miPuertoSerial.readLine()
    // devuelva 'true', lo que significa que leyó una línea.
    while (miPuertoSerial.readLine(buffer, 100)) {
        
        // Necesitamos una copia porque parsearTrama() modifica el buffer
        char buffer_parseo[100];
        strcpy(buffer_parseo, buffer);

        std::cout << "Trama recibida: [" << buffer << "]";

        // 4. Parsear e Instanciar
        TramaBase* tramaActual = parsearTrama(buffer_parseo);

        if (tramaActual != NULL) {
            // 5. Ejecutar (Polimorfismo)
            tramaActual->procesar(&miListaDeCarga, &miRotorDeMapeo);
            
            // 6. Limpiar
            delete tramaActual;
        } else {
            // Ignorar la trama "--- Flujo Terminado ---" del Arduino
            if (strcmp(buffer, "--- Flujo Terminado ---") != 0) {
                 std::cout << " -> Trama mal formada. Ignorando.";
            } else {
                std::cout << " -> Fin de transmision detectado.";
                break; // Salir del bucle while
            }
        }
        std::cout << std::endl;
    }

    // 7. Resultado Final
    std::cout << "\n---" << std::endl;
    std::cout << "Flujo de datos terminado o puerto desconectado." << std::endl;
    std::cout << "MENSAJE OCULTO ENSAMBLADO:" << std::endl;
    
    miListaDeCarga.imprimirMensaje(); 
    
    std::cout << "\n---" << std::endl;
    std::cout << "Liberando memoria... Sistema apagado." << std::endl;

    // 8. Desconectar
    miPuertoSerial.disconnect();

    return 0;
}