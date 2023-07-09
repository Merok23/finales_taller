/**
3) Escriba un pequeño programa que implemente un servidor TCP. El mismo debe recibir 
paquetes de datos de 8 bytes e imprimirlos en formato Hexadecimal (un paquete por 
renglón). El servidor debe cerrarse al recibir un paquete de 8 bytes 00h.
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
//'\0' == 0000 = 0 (para mi)
bool ended(char* buffer) {
    for (int i = 0; i < 8; i++) if (buffer[i] != '\0') return false;
    return true;
}

int main(int argc, char** argv) {
    //Suponiendo que me pasan un puerto por argv:
    if (argc != 2) return 1;
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
    if (error == -1) return 1;
    error = listen(file_descriptor, 5);
    int recieving_socket = accept(file_descriptor, nullptr, nullptr);
    bool finished = false;
    char buffer[9];
    buffer[8] = '\0';
    size_t recieved;
    while (!finished) {
        recieved = 0;
        while(recieved < 8) {
            recieved = recv(recieving_socket, buffer + recieved, 8, 0);
            if (recieved == -1 ) return 1; //aca se liberarian recursos
        }
        if (ended(buffer)) finished = true;
        printf("Recieved: %s", buffer);
    }
    freeaddrinfo(result);
    return 0;
}
