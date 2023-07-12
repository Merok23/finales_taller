#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#define FILE_PATH "nros_2bytes_bigend.bin"
/*
Escribir un programa ISO C MULTIPLATAFORMA que procese el archivo
“nros_2bytes_bigend.bin” sobre sí mismo, leyendo los nros (que están grabados en
bigendian) y eliminando los número múltiplos de 7
*/

int reWriteFile(FILE* file, off_t offset) {
    int16_t number;
    off_t writeOffset = offset;
    off_t readOffset = offset + 2;
    fseek(file, readOffset, SEEK_SET);
    int read = fread(&number, 2, 1, file);
    if(read == -1) return -1;
    readOffset += read;
    int error;
    while(read != EOF) {
        fseek(file, writeOffset, SEEK_SET);
        error = fwrite(&number, 2, 1, file);
        if (error == -1) return -1;
        writeOffset += error;
        fseek(file, readOffset, SEEK_SET);
        read = fread(&number, 2, 1, file);
        if (read == -1) return -1;
        readOffset += read;
    }
    return 0;
}

int eliminateInPlace(FILE* file) {
    int16_t number;
    size_t read = fread(&number, 2, 1, file);
    if (read == -1) return -1;
    number = ntohs(number); //paso de big endian (network) a cualquiera que sea mi maquina.
    off_t readOffset = read;
    off_t writeOffset = 0;
    while(read != EOF) {
        if (number % 7 == 0) {
            writeOffset = readOffset - 2;
            if (reWriteFile(file, writeOffset) < 0)
                return -1;
            readOffset -= 2; //saco 2 porque borre un elemento
        }
        fseek(file, readOffset, SEEK_SET);
        read = fread(&number, 2, 1, file);
        if(read == -1) return -1;
        readOffset += read;
        number = ntohs(number);
    }
    return 0;
}


int main (int argc, char** argv) {
    FILE* file = fopen(FILE_PATH, "r+");
    if(!file) return -1;
    if (eliminateInPlace(file)) {
        fclose(file);
        return -1;
    }
    fclose(file);
    return 0;
}