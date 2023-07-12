## 1. Escriba un programa (desde la inicialización hasta la liberación de los recursos) que reciba paquetes   de   la   forma   nnn+nn+....+nnnn=  (numeros separados por +, seguidos de =) e imprima el resultado de la suma de cada paquete por pantalla. Al recibir un paquete vacío (“=”)  debe cerrarse ordenadamente. No considere errores..

```c
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
```

## 2. Explique breve y concretamente qué es f:
int  (*f) (short *, char[4]);

f es un puntero de funcion, que recibe un puntero a short y un array de 4 chars, y devuelve un entero.

## 3. Analice el siguiente código y determine lo que se imprime (valor de Pi)
```c
main()
{
int *Pi=1000;
Pi++;
printf(“Pi apunta a la dirección: %l”, (long)Pi);
}
```
"Pi apunta a la direccion: 1004" (en realidad no imprime eso, porque para ver Pi se deberia usar %p)

## 4. ¿Qué es un functor? ¿Qué ventaja ofrece frente a una función convencional? Ejemplifique.
(MAL)
Un functor es una funcion encapsulada dentro de un objeto, es util para transformar en objetos a funciones que no tienen realmente un paralelo a ese paradigma (por ejemplo, threads), entonces, en vez de tener un hilo que hace cosas, se lo puede tener adentro de una clase, y llamarla "ClientThread" o "DonwloaderThread"

(BIEN)
Un functor, en el contexto de la programación orientada a objetos, se refiere a un objeto que puede comportarse como una función. Es un concepto que proviene de los lenguajes de programación que admiten la sobrecarga del operador de llamada de función, como C++.

Un functor se define mediante una clase que implementa el operador de llamada de función (operator()). Esto permite que el objeto de esa clase se utilice como si fuera una función, es decir, puede ser invocado con los paréntesis de la misma manera que se invoca una función convencional.

**La ventaja principal de los funtores es que pueden almacenar un estado interno y mantener información adicional entre llamadas sucesivas.** Esto les proporciona una ventaja sobre las funciones convencionales, ya que una función regular no tiene memoria entre invocaciones consecutivas, mientras que un functor puede retener su estado.

```c++
#include <iostream>

class Incrementador {
public:
    Incrementador(int incremento) : incremento_(incremento) {}

    int operator()(int valor) {
        return valor + incremento_;
    }

private:
    int incremento_;
};

int main() {
    Incrementador incrementador(5);
    int resultado = incrementador(10);
    std::cout << "Resultado: " << resultado << std::endl; // Imprime "Resultado: 15"

    return 0;
}
```

## 5. ¿Cómo se logra que 2 threads accedan (lectura/escritura) a un mismo recurso compartido sin que se generen problemas de consistencia? Ejemplifique.

Para lograr que 2 threads accedan a un mismo recurso compartido con accesos de lectura y escritura, se pude utilizar un mutex (mutual exclusion), por ejemplo, si se tiene un contador en C++:

```c++
class ContadorMonitor {
    private:
        std::mutex mtx;
        int i;
    public:
        //...
        int add() {
            std::lock_guard<std::mutex> lock(mtx);
            i++;
            return i;
        }

        int get() {
            std::lock_guard<std::mutex> lock(mtx);
            return i;
        }
        //...
}
```

Si varios threads quieren usar el contador, entonces no hay problema, pues solo se puede sumar de a uno, y todos se bloquean tratando de obtener el mutex cuando se esta usando.

## 6. Describa el concepto de loop de eventos (events loop) utilizado en programación orientada a eventos y, en particular, en entornos de interfaz gráfica (GUIs).

Un loop de eventos es cuando uno se queda a la espera de determinados eventos (por ejemplo el usuario presiona una telca), y cuando llega esa se;al, se hace algo al respecto en el programa (se procesa el evento), y despues se queda a la espera de otro evento.

## 7.Considere la estructura struct ejemplo { int a; char b;}. ¿Es verdad que sizeof  (ejemplo)=sizeof(a)+sizeof(b)? Justifique.

no necesariamente, pues puede haber padding en el medio, para que eso sea verdad habria que agregarle el atributo packed a la estructura.
{
a 4
2 bytes padding
b 4
}
Siempre depende de la compilacion, procesador, y diferentes variables del sistema operativo.

## 8. ¿En qué consiste el patrón de diseño RAII? Ejemplifique.
Resource adquisition is initialization es un patron de dise;o que consiste en adquirir todos los recursos al momento de instanciar el objeto, y que esten todos operacionales y listos para ser usados cuando el objeto esta creado,
por ejemplo:

```c++
class Contador {
    private:
        int i; //recurso que hay que inicializar
    public:
        Contador() : i(0) {}; //se inicializa en 0, en caso de que no se pueda, nunca se crea la instancia de contador.
}
```
Tambien en C++, se asegura que los recursos sean liberados cuando la instancia se va de su respectivo scope, y eso se logra llamando al destructor, por lo tanto en el destructor debe estar tambien la liberacion de los recursos.
Esto ayuda a abstraerse de temas de memoria, sabiendo que son liberados correctamente en un solo lugar, y son adquiridos en otro lugar.
## 9. Escribir un programa ISO C  que procese el archivo de  enteros de 2 bytes bigendian cuyo nombre es recibido como parámetro.  El procesamiento consiste en  eliminar los número múltiplos   de   3,  trabajando sobre el mismo archivo (sin archivos intermedios ni en memoria).

```c
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
```

## 10. Implemente una función C++ denominada DobleSiNo que reciba dos listas de elementos y devuelva una nueva lista  duplicando   los   elementos   de   la   primera   que   no   están   en   la segunda:
               std::list<T> DobleSiNo(std::list<T> a,std::list<T> b);

```C++
#include <stdlib.h>
#include <iostream>
#include <list>

std::list<int> dobleSiNo(std::list<int> a,std::list<int> b) {
    bool found = false;
    std::list<int> elementsNotFound;
    for (auto&& elementA : a) {
        for (auto&& elementB : b) {
            if (elementA == elementB) {
                found = true;
                break;
            }
        }
        if (!found) elementsNotFound.push_back(elementA);
        found = false;
    }
    for (auto&& element : elementsNotFound) {
        a.push_back(element);
    }
    return a;
}



int main (int argc, char** argv) {
    std::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::list<int> b = {1, 3, 5, 7, 9};
    std::list<int> result = dobleSiNo(a, b);
    for (auto&& res : result) {
        std::cout << res << " ";
    }
    std::cout << std::endl;
    return 0;
}
```