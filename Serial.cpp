#include "Serial.h"

// Solo compilar este código en Windows
#ifdef _WIN32

Serial::Serial() {
    this->hSerial = INVALID_HANDLE_VALUE;
    this->connected = false;
}

Serial::~Serial() {
    if (this->connected) {
        this->disconnect();
    }
}

bool Serial::connect(const char* portName, DWORD baudRate) {
    char fullPortName[20];
    sprintf_s(fullPortName, sizeof(fullPortName), "\\\\.\\%s", portName);

    this->hSerial = CreateFileA(
        fullPortName,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (this->hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error al abrir el puerto: " << portName << std::endl;
        return false;
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(this->hSerial, &dcbSerialParams)) {
        std::cerr << "Error al obtener estado del COM" << std::endl;
        CloseHandle(this->hSerial);
        return false;
    }

    dcbSerialParams.BaudRate = baudRate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(this->hSerial, &dcbSerialParams)) {
        std::cerr << "Error al configurar estado del COM" << std::endl;
        CloseHandle(this->hSerial);
        return false;
    }

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50; 
    timeouts.ReadTotalTimeoutConstant = 50; 
    timeouts.ReadTotalTimeoutMultiplier = 10; 

    if (!SetCommTimeouts(this->hSerial, &timeouts)) {
        std::cerr << "Error al configurar timeouts" << std::endl;
        CloseHandle(this->hSerial);
        return false;
    }

    this->connected = true;
    std::cout << "Conexion establecida en " << portName << " a " << baudRate << std::endl;
    return true;
}

void Serial::disconnect() {
    if (this->connected) {
        CloseHandle(this->hSerial);
        this->hSerial = INVALID_HANDLE_VALUE;
        this->connected = false;
        std::cout << "Puerto desconectado." << std::endl;
    }
}

bool Serial::readLine(char* buffer, unsigned int bufferSize) {
    if (!this->connected) return false;

    char receivedChar;
    DWORD bytesRead;
    unsigned int charCount = 0;

    while (charCount < (bufferSize - 1)) {
        
        if (ReadFile(this->hSerial, &receivedChar, 1, &bytesRead, NULL)) {
            if (bytesRead > 0) {
                if (receivedChar == '\r') {
                    continue; 
                }
                
                if (receivedChar == '\n') {
                    buffer[charCount] = '\0'; // Terminar el string
                    return true; 
                }
                
                buffer[charCount] = receivedChar;
                charCount++;
            }
        } else {
            std::cerr << "Error en ReadFile" << std::endl;
            return false;
        }
    }
    
    std::cerr << "Error: Buffer de lectura excedido." << std::endl;
    buffer[charCount] = '\0'; 
    return false;
}

#endif // _WIN32