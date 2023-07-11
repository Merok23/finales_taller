cmake_minimum_required(VERSION 3.26)
project(final)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Release)

# source files
file(GLOB EJ_UNO desplazarContenido.c)
file(GLOB EJ_TRES ejercicioDeadLock.cpp)
file(GLOB EJ_SEIS envioHastaFin.cpp)
file(GLOB EJ_ROMBO romboAmarillo.cpp)


# Find SDL2 packages
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

# Find SDL2pp package
find_package(SDL2pp REQUIRED)

# Include SDL2pp headers
include_directories(${SDL2PP_INCLUDE_DIRS})

# binaries
add_executable(desplazarContenido ${EJ_UNO})
add_executable(ejercicioDeadLock ${EJ_TRES})
add_executable(envioHastaFin ${EJ_SEIS})
add_executable(rombo ${EJ_ROMBO})

target_link_libraries(ejercicioDeadLock
    pthread
)

# Link SDL2 and SDL2pp libraries
target_link_libraries(rombo
    SDL2pp
    SDL2_gfx
    ${SDL2_LIBRARIES}
)
