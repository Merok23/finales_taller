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

## 3. Escriba un pequeño programa que implemente un servidor TCP. El mismo debe recibir paquetes de datos de 8 bytes e imprimirlos en formato Hexadecimal (un paquete por renglón). El servidor debe cerrarse al recibir un paquete de 8 bytes 00h.

```c
//asumo que el byte 0 == '\0'
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
```

## 4. ¿Qué significado tiene el modificar const en C++? Ejemplifique.
El modificador const en los parametros y variables en C++ significa que el parametro o variable es constante y no se debería modificar el varlo de dicha variable. En la practica para lograr esto, lo que se hace es que el compilador checkea al momento de compilar si se esta modificando esa varible, si es asi, tira un error de compilación. Mas que nada suele ser una herramienta que sirve para evitar errores humanos, y suele ser buena practica que si se sabe que un parametro o variable deberia ser constante, ponerle el modificador const.

## 5. Describa qué tipos de variables y atributos de clases se guardan en los diferentes areas de memoria (stack, data segment, heap, code segment).
code: Las variables globales, normalmente con el modificador extern.
data: Las variables estaticas, que viven dentro de un archivo y pueden ser referenciadas desde cualquier lugar de ese archivo (y mantienen su valor a lo largo de la ejecución).
heap: Las variables que se encuentran en memoria dinamica, es decir, memoria manejada por el programador. Suele ser adquirida con malloc o new en C/C++, y deben ser liberadas por el programador.
stack: Todas las variables dentro de funciones, que dejan de existir una vez se termina la funcion en la que estan. (se van de su scope)

## 6. Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje, en color azul, un óvalo que ocupe toda la pantalla.
handleEvents es solo para cerrar la ventana, lo importante esta en main.
```c
#define WIDTH 1366
#define HEIGHT 768

bool handleEvents() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_QUIT:
                return true;
        }
    }
    return false;
}

int main (int argc, char** argv) {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    SDL2pp::Window mainWindow("ovalo", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL2pp::Renderer renderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    bool closed = false;
    while(!closed) {
        closed = handleEvents();
        renderer.SetDrawColor(0xff, 0xff, 0xff);
        renderer.Clear();
        //renderer position_x, position_y, radius_x, radius_y, red, green, blue, alpha
        filledEllipseRGBA(renderer.Get(), WIDTH/2, HEIGHT/2, WIDTH/2, HEIGHT/2, 0, 0, 255, 255);
        renderer.Present();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 30));
    }
    return 0;
}
```

## 7. ¿Qué son las funciones virtuales? ¿Para qué sirven? De un breve ejemplo de su uso.

Las funciones virtuales son funciones que uno puede redefinir en las clases hijas, aunque no es necesario hacerlo. Es decir, la funcion puede tener un comportamiento genérico por default, pero si se necesita que se haga otra cosa, mediante "override" se puede redefinir. Clasico ejemplo de los animales:
```C++
class perro {
    pubic:
        virtual void communicate() {
            std::cout << "Guau" << std::endl;
        }

}

class chihuaha : public perro {
    public:
    virtual void communicate() override {
        std::cout << "Guau agudo" << std::endl;
    }
}
```

## 8. Declare una clase LongChar para encapsular un carácter en un campo de 16 bits. Incluya al menos: Constructor default, con char y Constructor de Copia; Operador <, ==, =, int y >>. Implemente el operador >>.

```C++
class LongChar {
    private:
        char myChar[2];
    public:
        LongChar();
        LongChar(const char &c);
        bool operator<(const LongChar &other) const;
        bool operator==(const LongChar &other) const;
        LongChar& operator=(const LongChar &other);
        operator int() const;
        void setLongChar(const char* longChar) {
            memcpy(this->myChar, longChar, 2);
        }
};

std::istream& operator>>(std::istream& in, LongChar& c) {
    char newLong[2];
    in >> newLong[0];
    in >> newLong[1];
    c.setLongChar(newLong);
    return in;
}
```

## 9. ¿Qué función utiliza para lanzar un thread? Explique su uso mediante un ejemplo sencillo.

La función que se utiliza para lanzar un thread en C++ es std::thread(void*, void* args), donde el primer parametro es la función que se quiere utilizar, y los parametros que siguen son los parametros de esa función, por ejemplo, si queremos sumar todos los elementos de un array, podemos hacer lo siguiente:
```C++
void sumarElementos(const int* vector, const int &inicio, const int &largo, int &resultado){
    for (int i = inicio; i < largo; i++) resultado += vector[i];
}

int main(int argc, char** argv) {
    int superVector[10000]; // assuming the array is filled with numbers worth summing
    int resultado1 = 0;
    int resultado2 = 0;
    std::thread t1(sumarElementos, std::cref(superVector), 0, 5000, std::ref(resultado1));
    std::thread t2(sumarElementos, std::cref(superVector), 5000, 10000, std::ref(resultado2));
    t1.join();
    t2.join();
    std::cout << "El resultado es: " << resultado1 + resultado2 << std::endl;
    return 0;
}
```

## 10. Imagine que tiene que diseñar un protocolo de comunicaciones entre dos procesos que intercambiarán paquetes de datos. ¿Qué alternativas puede imaginar para implementar el concepto de paquete (para que el receptor determine cuando termina un paquete e inicia el siguiente)?

Se pueden usar varios metodos, por ejemplo, se puede enviar la longitud del paquete al principio de cada paquete, tener un largo predefinido para todos los paquetes, o enviar un valor especifico que se acordo que es el final de un paquete. 