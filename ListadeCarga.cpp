#include "ListaDeCarga.h"
#include <cstddef> // Para NULL

ListaDeCarga::ListaDeCarga() {
    inicio = NULL;
    fin = NULL;
}

ListaDeCarga::~ListaDeCarga() {
    NodoCarga* actual = inicio;
    NodoCarga* nodoAEliminar;

    while (actual != NULL) {
        nodoAEliminar = actual;
        actual = actual->siguiente;
        delete nodoAEliminar;
    }
    inicio = NULL;
    fin = NULL;
}

void ListaDeCarga::insertarAlFinal(char dato) {
    NodoCarga* nuevoNodo = new NodoCarga();
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->previo = fin;

    if (fin != NULL) {
        fin->siguiente = nuevoNodo;
    }

    fin = nuevoNodo;

    if (inicio == NULL) {
        inicio = nuevoNodo;
    }
}

void ListaDeCarga::imprimirMensaje() {
    NodoCarga* actual = inicio;
    
    while (actual != NULL) {
        std::cout << "[" << actual->dato << "]";
        actual = actual->siguiente;
    }
}