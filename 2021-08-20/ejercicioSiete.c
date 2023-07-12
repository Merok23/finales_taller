/*
7. Escriba un programa que reciba por línea de comandos un Puerto y una IP. 
El programa debe conectarse al destino indicado y quedar en escucha de paquetes con la forma “d..d,d..d,… =”. 
El programa debe imprimir en stdout el checksum (sumatoria módulo 256) de cada paquete. 
Cuando se reciba un paquete vacío se debe finalizar ordenadamente.
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char** argv) {
    if (argc != 3) return -1;
    char* ip = argv[1];
    char* port = argv[2];
    struct addrinfo hints;
    struct addrinfo* results;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AI_INET;

    int error = getaddrinfo(ip, port, &hints, &results);
    if (error < 0) {
        freeaddrinfo(results);
        return -1;
    }
    int sfd = socket(results->ai_family, results->ai_socktype, results->ai_prototype);
    if (sdf == -1) {
        freeaddrinfo(results);
        return -1;
    }
    error = connect(sdf, results->ai_addr, results->ai_addrlen);
    if (error == -1) {
        freeaddrinfo(results);
        return -1;
    }

    bool finished = false;
    while (!finished) {
        //igual a lo demas, igual no entiendo el enunciado
    }
    freeaddrinfo(results);
    shutdown(sdf, SHUT_RDWR);
    close(sdf);
    return 0;
}