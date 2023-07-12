/*
Escribir un programa ISO C  que procese el archivo de  enteros de 2 bytes bigendian cuyo nombre es recibido como parámetro.  
El procesamiento consiste en  eliminar los número múltiplos   de   3,  trabajando sobre el mismo archivo (sin archivos intermedios ni en memoria).
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int reescribirArchivo(FILE* archivo, int offsetLectura) {
    int offsetEscritura = offsetLectura - 2;
    int16_t numero;
    int read = fread(&numero, 2, 1, archivo);
    if (read == -1) return -1;
    //offsetLectura no es modificado pues es una copia
    offsetLectura += read; 
    fseek(archivo, offsetEscritura, SEEK_SET);
    int write = fwrite(&numero, 2, 1, archivo);
    if (write == -1) return -1; //exploto todo
    offsetEscritura += write;
    while (read != EOF) {
        fseek(archivo, offsetLectura, SEEK_SET);
        read = fread(&numero, 2, 1, archivo);
        if (read == -1) return -1;
        offsetLectura += read;
        fseek(archivo, offsetEscritura, SEEK_SET);
        write = fwrite(&numero, 2, 1, archivo);
        if (write == -1) return -1;
        offsetEscritura += write;
    }
    return 0;
}

int eliminarMultiplosDeTres(FILE* archivo) {
    int16_t numero;
    int read = fread(&numero, 2, 1, archivo);
    int offsetLectura = read;
    while(read != EOF) {
        numero = ntohs(numero);
        if (numero % 3 == 0) {
            if (reescribirArchivo(archivo, offsetLectura) < 0) {
                return -1;
            }
        }
        fseek(archivo, offsetLectura, SEEK_SET);
        read = fread(&numero, 2, 1, archivo);
        offsetLectura += read;
    }
    return 0;
}



int main(int argc, char** argv) {
    if (argc != 2) return -1;

    FILE* archivo = fopen(argv[1], "r+");
    if (!archivo) return -1;
    if (eliminarMultiplosDeTres(archivo) < 0) {
        printf("error");
        fclose(archivo);
        return -1;
    }
    fclose(archivo);
    return 0;
}