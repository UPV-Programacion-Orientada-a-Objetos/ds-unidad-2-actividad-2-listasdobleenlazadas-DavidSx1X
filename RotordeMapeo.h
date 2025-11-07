#ifndef ROTORDEMAPEO_H
#define ROTORDEMAPEO_H

struct NodoRotor {
    char dato;
    NodoRotor* siguiente;
    NodoRotor* previo;
};

class RotorDeMapeo {
private:
    NodoRotor* cabeza;
    
public:
    RotorDeMapeo();
    ~RotorDeMapeo();
    void rotar(int N);
    char getMapeo(char in);
};

#endif // ROTORDEMAPEO_H