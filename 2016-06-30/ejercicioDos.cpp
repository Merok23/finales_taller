/**
3) Escriba un pequeño programa que implemente un servidor TCP. El mismo debe recibir 
paquetes de datos de 8 bytes e imprimirlos en formato Hexadecimal (un paquete por 
renglón). El servidor debe cerrarse al recibir un paquete de 8 bytes 00h.
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
int main(int argc, char** argv) {
    //Suponiendo que me pasan un puerto por argv:
    if (argc != 2) return;
    char* port = argv[1];
    //struct que nos llena addrinfo
    struct addrinfo hints;
    struct addrinfo *result;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;//Stream, porque es tcp
    hints.ai_flags = AI_PASSIVE;//pasivo porque es un server

    int error = getaddrinfo(NULL, port, &hints, &result);//asumo que no tiene errores:
    int file_descriptor = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    //bindeamos el socket para aceptar conecciones:
    error = bind(file_descriptor, result->ai_addr, result->ai_addrlen);

    return 0;
}