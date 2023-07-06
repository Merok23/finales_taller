## 1. Escribir un programa ISO C que procese el archivo numero.txt (numeros decimales de 5 dígitos separados por espacio) sobre sí mismo. El proceso consiste en leer un número y escribirlo como 4 dígitos hexadecimales con 1 espacio separador.

```c
void translateToHexa(const char* fileName) {
    FILE* file = fopen(fileName, "rw+");
    if (!file) return;
    int number;
    size_t read = fscanf(file, "%5d", &number);
    off_t offsetEscritura = 0;
    off_t offsetLectura = 6;
    while(read != EOF) {
        // seteo el offset, scanf lo adelanta, yo vuelvo al ultimo escrito
        fseek(file, offsetEscritura, SEEK_SET);
        offsetEscritura += fprintf(file, "%04X ", number);
        // el offset de escritura termina estando mucho atras, por eso dos offsets
        fseek(file, offsetLectura, SEEK_SET);
        read = fscanf(file, "%5d", &number);
        offsetLectura += 6;
    }
    truncate(fileName, offsetEscritura);
    fclose(file);
}

int main(int argc, char** argv) {
    translateToHexa("archivo.txt");
    return 0;
}
```

## 2. Describa y ejemplifique el uso de la siguiente instrucción de precompilación: #if.

La instruccion de compilacion #if es una instruccion para el compilador que, al momento de compilar, evalua la condicion puesta seguida de #if (por ejemplo #if true), si esta se cumple, el compilador toma en cuenta el codigo debajo de #if. Si no, el codigo nunca se compila, por lo tanto es como si no estuviese escrito. Un posible uso para esto es hacer un modo para debuguear un programa, por ejemplo:
```
#define DEBUG_MODE false

#if DEBUG_MODE true

//codigo

#endif
```
Cambiando el valor de DEBUG_MODE, se va a compilar lo que este entre #if y #endif.

## 