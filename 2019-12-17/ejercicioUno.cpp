/**
Escriba un programa (desde la inicialización hasta la liberación de los recursos) que reciba
paquetes   de   la   forma   nnn+nn+....+nnnn=  (numeros separados por +, seguidos de =) e
imprima el resultado de la suma de cada paquete por pantalla. Al recibir un paquete vacío
(“=”)  debe cerrarse ordenadamente. No considere errores..
*/
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//asumo que "n" es un caracter de numero (1byte) y no un entero de 4 bytes.
int main (int argc, char** argv) {
    //asumo que se conecta a otro proceso, y no que espera recibir una coneccion:
    if (argc != 3) return -1;
    char* ip = argv[1];
    char* port = argv[2];
    struct addrinfo hints;
    struct addrinfo* results;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    getaddrinfo(ip, port, &hints, &results);
    //asumo encuentra a la primera
    int sdf = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    if (sdf == -1) return -1;
    connect(sdf, results->ai_addr, results->ai_addrlen);
    bool finished = false;
    int resultado = 0;
    char number[2] = {'\0'};
    int read = 0;
    int sent = 0;
    while(!finished) {
        read = recv(sdf, number, 1, 0);
        if (strcmp(number, "=") == 0) {
            finished = true;
            continue;
        }
        if (read == -1) break;
        char completeNumber[100] = {'\0'};
        while (strcmp(number, "=") != 0 && strcmp(number, "+") != 0) {
            strcat(completeNumber, number);
            read = recv(sdf, number, 1, 0);
        }
        int current = atoi(completeNumber);
        resultado += current;
        if (strcmp(number, "=") == 0) {
            printf("El resultado de este paquete es: %d", resultado);
            resultado = 0;
        }

    }
    shutdown(sdf, SHUT_RDWR);
    close(sdf);
    freeaddrinfo(results);
    return 0;
}