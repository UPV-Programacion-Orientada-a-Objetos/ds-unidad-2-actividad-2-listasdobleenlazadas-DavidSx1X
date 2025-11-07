#ifndef TRAMA_H
#define TRAMA_H

// Declaraciones adelantadas
class ListaDeCarga;
class RotorDeMapeo;

class TramaBase {
public:
    virtual ~TramaBase() {}
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
};


class TramaLoad : public TramaBase {
private:
    char fragmento;

public:
    TramaLoad(char frag) : fragmento(frag) {}
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};


class TramaMap : public TramaBase {
private:
    int rotacion;

public:
    TramaMap(int rot) : rotacion(rot) {}
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMA_H