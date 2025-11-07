#ifndef LISTADECARGA_H
#define LISTADECARGA_H

#include <iostream>

struct NodoCarga {
    char dato;
    NodoCarga* siguiente;
    NodoCarga* previo;
};

class ListaDeCarga {
private:
    NodoCarga* inicio;
    NodoCarga* fin;

public:
    ListaDeCarga();
    ~ListaDeCarga();
    void insertarAlFinal(char dato);
    void imprimirMensaje();
};

#endif // LISTADECARGA_H