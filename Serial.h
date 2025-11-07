#ifndef SERIAL_H
#define SERIAL_H

// Solo compilar este código en Windows
#ifdef _WIN32

#include <windows.h> // API de Windows
#include <stdio.h>   // Para printf
#include <iostream>  // Para std::cerr

class Serial {
private:
    HANDLE hSerial; 
    bool connected;

public:
    Serial();
    ~Serial();
    bool connect(const char* portName, DWORD baudRate = 9600);
    void disconnect();
    bool readLine(char* buffer, unsigned int bufferSize);
};

#else
// Stub para otros SO
#include <iostream>
class Serial {
public:
    Serial() { std::cerr << "Serial no implementado para este SO." << std::endl; }
    ~Serial() {}
    bool connect(const char* portName, unsigned long baudRate = 9600) { return false; }
    void disconnect() {}
    bool readLine(char* buffer, unsigned int bufferSize) { return false; }
};
#endif // _WIN32
#endif // SERIAL_H