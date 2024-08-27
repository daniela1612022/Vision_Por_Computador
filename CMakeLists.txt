cmake_minimum_required(VERSION 3.16)

project(Punto1 LANGUAGES CXX)

# Configuración de CMake para manejar automáticamente UIC, MOC y RCC en Qt (si fuera necesario)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Establecer el estándar de C++ a usar
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar las bibliotecas necesarias de OpenCV
find_package(OpenCV REQUIRED)

# Incluir directorios de OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Ejercicio 1: Generar ejecutable para punto1.cpp
add_executable(Ejercicio1 punto1.cpp)
target_link_libraries(Ejercicio1 ${OpenCV_LIBS})

# Ejercicio 2: Generar ejecutable para punto2.cpp
add_executable(Ejercicio2 punto2.cpp)
target_link_libraries(Ejercicio2 ${OpenCV_LIBS})

# Ejercicio 3: Generar ejecutable para punto3.cpp
add_executable(Ejercicio3 punto3.cpp)
target_link_libraries(Ejercicio3 ${OpenCV_LIBS})

# Ejercicio 4: Generar ejecutable para punto4.cpp
add_executable(Ejercicio4 punto4.cpp)
target_link_libraries(Ejercicio4 ${OpenCV_LIBS})

# Opcional: Incluir instalación de los ejecutables
install(TARGETS Ejercicio1 Ejercicio2 Ejercicio3 Ejercicio4
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
