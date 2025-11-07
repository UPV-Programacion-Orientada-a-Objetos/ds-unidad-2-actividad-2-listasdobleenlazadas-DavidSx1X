cmake_minimum_required(VERSION 3.10)

# Define el proyecto
project(PRT7_Decoder CXX)

# Establece el estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Agrega todos los archivos fuente para crear el ejecutable "Decoder"
add_executable(Decoder
    main.cpp
    Trama.h
    Trama.cpp
    RotorDeMapeo.h
    RotorDeMapeo.cpp
    ListaDeCarga.h
    ListaDeCarga.cpp
    Serial.h
    Serial.cpp
)

# En Windows, necesitamos enlazar con 'kernel32' para las funciones de puerto
if(WIN32)
    target_link_libraries(Decoder kernel32)
endif()

message(STATUS "Proyecto PRT-7 Decoder configurado.")