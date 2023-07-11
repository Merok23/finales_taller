#include <stdio.h>
#include <stdlib.h>

int desplazarContenido(FILE* file, unsigned offset, unsigned len, int delta) {
    fseek(file, offset, SEEK_SET); // establecer la posición en el desplazamiento
    char* megaString = malloc(len * sizeof(char));
    if (!megaString) return -1; // error de asignación de memoria
    size_t read = fread(megaString, sizeof(char), len - offset, file);
    if (ferror(file)) {
        free(megaString);
        return -1; // error de lectura
    }
    fseek(file, delta, SEEK_CUR); // mover la posición actual delta posiciones hacia adelante o hacia atrás
    size_t write = fwrite(megaString, sizeof(char), len - offset, file);
    if (write != len - offset) {
        free(megaString);
        return -1; // error de escritura
    }
    len += delta;
    if (ftruncate(fileno(file), len) != 0) {
        free(megaString);
        return -1; // error de truncado
    }
    free(megaString);
    return 0;
}

int main(int argc, char** argv) {
    FILE* file = fopen("desplazarContenido.txt", "r+");
    if (!file) {
        perror("No se pudo abrir el archivo");
        return -1;
    }
    if (desplazarContenido(file, 1, 1, 1) < 0) {
        perror("Error al desplazar el contenido");
        fclose(file);
        return -1;
    }
    fclose(file);
    return 0;
}
