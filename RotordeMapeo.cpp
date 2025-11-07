#include "RotorDeMapeo.h"
#include <cstddef> // Para NULL

RotorDeMapeo::RotorDeMapeo() {
    cabeza = NULL;
    NodoRotor* previo = NULL;
    NodoRotor* primerNodo = NULL;

    for (char c = 'A'; c <= 'Z'; ++c) {
        NodoRotor* nuevoNodo = new NodoRotor();
        nuevoNodo->dato = c;
        nuevoNodo->siguiente = NULL;
        nuevoNodo->previo = previo;

        if (previo != NULL) {
            previo->siguiente = nuevoNodo;
        }

        if (c == 'A') {
            cabeza = nuevoNodo;
            primerNodo = nuevoNodo;
        }

        previo = nuevoNodo;
    }

    if (previo != NULL && primerNodo != NULL) {
        previo->siguiente = primerNodo;
        primerNodo->previo = previo;
    }
}

RotorDeMapeo::~RotorDeMapeo() {
    if (cabeza == NULL) return;

    NodoRotor* actual = cabeza;
    NodoRotor* nodoAEliminar;
    
    cabeza->previo->siguiente = NULL;

    while (actual != NULL) {
        nodoAEliminar = actual;
        actual = actual->siguiente;
        delete nodoAEliminar;
    }
}

void RotorDeMapeo::rotar(int N) {
    if (cabeza == NULL) return;

    if (N > 0) {
        for (int i = 0; i < N; ++i) {
            cabeza = cabeza->siguiente;
        }
    } else if (N < 0) {
        int pasosAtras = -N; 
        for (int i = 0; i < pasosAtras; ++i) {
            cabeza = cabeza->previo;
        }
    }
}

char RotorDeMapeo::getMapeo(char in) {
    if (in < 'A' || in > 'Z') {
        return in;
    }

    int offset = in - 'A';
    NodoRotor* temp = cabeza;

    for (int i = 0; i < offset; ++i) {
        temp = temp->siguiente;
    }

    return temp->dato;
}