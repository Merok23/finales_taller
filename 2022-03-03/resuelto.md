## Explique que es cada uno de los siguientes, haciendo referencia a su **scope, lifetime, valor de inicializacion** y el **area de memoria** donde reside.
- Una variable global static
- Una variable global
- Una variable local static
- Una variable local
- Un atributo de clase static
- Un atributo de clase
  
### Una variable global static:
- Scope: El archivo donde esta declarada
- Lifetime: Todo el tiempo de ejecución (si fue cargado de forma dinamica, solo cuando se carga el archivo en adelante)
- Valor de inicialización: El que se le asigna, o indefinido(0).
- Area de memoria: Data Segment.
### Una variable global:
- Scope: Cualquier archivo que le haga extern
- Lifetime: Todo el tiempo de ejecución (si fue cargado de forma dinamica, solo cuando se carga el archivo en adelante)
- Valor de inicialización: El que se le asigna, o indefinido.
- Area de memoria: Data Segment.
### Una variable local static
- Scope: La funcion en la que esta declarada
- Lifetime: Todo el tiempo de ejecución (si fue cargado de forma dinamica, solo cuando se carga el archivo en adelante)
- Valor de inicialización: El que se le asigna, o indefinido(0). Se mantiene entre llamados de funcion.
- Area de memoria: Data Segment.
### Una variable local
- Scope: La funcion en la que esta declarada
- Lifetime: Hasta que se termina la funcion en la que esta declarada.
- Valor de inicialización: El que se le asigna, o indefinido.
- Area de memoria: Stack Segment.
### Un atributo de clase static
- Scope: Global a la instancia de la clase, y si es publico se puede acceder desde cualquier lado con Clase::atributo.
- Lifetime: Desde que se instancia la clase.
- Valor de inicialización: El que se le asigna, o indefinido.
- Area de memoria: Data Segment. 
### Un atributo de clase
- Scope: La instancia donde esta el atributo.
- Lifetime: Desde que se instancia el objeto, hasta que se va la instancia de scope.
- Valor de inicialización: El que se le asigna(en el constructor), o indefinido.
- Area de memoria: Stack Segment (con opcion a heap si asi lo hizo el programador).

## Que es un DeadLock? Ejemplifique mediante codigo que constituya un indefictible caso. 

```c++
std::mutex unMutex;
void funcionSusUno() {
    std::lock_guard<std::mutex> lock(unMutex);
    std::cout << "Aca nunca se llega" << std::endl;
}

int main (int argc, char** argv) {
    std::lock_guard<std::mutex> lock(unMutex);
    std::thread t1(funcionSusUno);
    t1.join();
    return 0;
}
```

## Que es una Mutex? Ejemplifique mediante codigo.
Un mutex es un mecanismo de sincronizacion de threads, se usa para evitar race conditions, ya que si se quiere compartir un recurso entre dos threads, el mutex hace que solo un hilo a la vez pueda acceder a una seccion de codigo en particular.

```c++
int i = 0;
std::mutex mutex;
int contarDiez() {
    std::lock_guard<std::mutex> lock(unMutex);
    for (int j = 0; j < 10; j++) i++;
    if (i % 2) std::cout << "Esto sin el mutex no sale siempre" << std::endl;
}

int main(int argc, char** argv) {
    std::thread t1(contarDiez);
    std::thread t2(contarDiez);
    t1.join();
    t2.join();
}
```
En el ejemplo, tanto t1 como t2 comparten el entero i, y si se sacase el mutex, no se podria asegurar que se imprima en pantalla el cout dos veces, sin embargo, con el mutex, se va a imprimir tantas veces como se ejecute la funcion.

## Escriba un programa que reciba por linea de comandos un puerto y una ip, el programa debe establecer una unica conexion, y enviar todo el texto recibido(del mismo socket). Cuando se reciba el texto "FIN", debe finalizar de forma ordenada sin enviar "FIN".

```c++
bool checkFinish(char* buffer) {
    char string[4];
    memcpy(string, buffer, 3);
    string[3] = '\0';
    if (strcmp("FIN", string) == 0) return true;
    return false;
}

int main (int argc, char** argv) {
    if (argc != 3) return 1;
    char* ip = argv[1];
    char* port = argv[2];
    struct addrinfo hints;
    struct addrinfo* result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    int error = getaddrinfo(ip, port, &hints, &result);
    if (error == -1) return 1;
    int sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sfd == -1) {
        freeaddrinfo(result);
        return 1;
    }
    bool finished = false;
    size_t size_read = 0;
    size_t size_sent = 0;
    char buffer[3];
    while(!finished) {
        while (size_read < 3) {
            error = recv(sfd, buffer, 3, 0);
            if (error == -1) return 1; //and freeaddrinfo
            size_read += error;
        }
        size_read = 0;
        finished = checkFinish(buffer);
        if (finished) continue;
        while (size_sent < 3) {
            error = send(sfd, buffer, 3, 0);
            if (error == -1) return 1; //and freeaddrinfo
            size_sent += error;
        }
    }
    freeaddrinfo(result);
    shutdown(sfd, SHUT_RDWR);
    close(sfd);
}
```

## Escriba una funcion ISO C prototipada int DesplazarContenido(FILE* file, unsigned offset, unsigned lenght, int delta) que desplace en <delta> posiciones (para adelante o para atras) el contenido del archivo <file> delimitado por <lenght> bytes desde <offset>. Debe devolver 0 si salio todo bien, < 0 si no.

```c
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
```
(Si pide hacerlo inplace, ese codigo no sirve).

## Declare una clase a eleccion considerando:
- Atributos que considere necesarios
- Accesibilidad de la clase
- Incluir operadores -, ++ (post incremento), -- (preIncremento), << (Impresion), >> Carga desde consola, int (cast a int)

```c++
class Contador {
    private:
        int i;
    public:
        Contador(int base);
        Contador operator-(const Contador& contador) const;
        Contador operator++(int); //post, devuelve una copia porque hola = otro++;
        Contador& operator--(); //pre, se devuelve a si mismo(*this), asique referencia --i;
        int getNumero();
        operator int() const;
};

std::ostream& operator<<(std::ostream &out, const Contador& contador);

std::istream& operator>>(std::istream &in, Contador& contador);
```

## Explique y ejemplifique el uso de la directiva de pre compilacion #if, #else, #endif.

Las directivas de precompilacion #if, #else, y #endif, se utilizan para darle una logica de compilacion al compilador, es decir, dada una variable de entorno, o definida con #define, se puede indicarle al compilador, que fragmentos de codigo compilar o no compilar. Por ejemplo:

```c
#define DEBUG false

int main(int argc, char** argv) {
    #if DEBUG
        printf("Argc es: %d\n", argc);
    #else
        if (argc != 4) {
            return -1;
        }
    #endif
    // ...
    return 0;
}
```

## Se puede evitar que un objeto de una clase sea copiado? y clonado? Explicar como si se puede, y por que no si no se puede.

Si, se puede, para que un objeto no sea copiado, se le puede borrar el constructor por copia, y para que no sea clonado, se le puede borrar el operador =:
```c++
//...
private:
    Clase& operator=(const Clase& other) = delete;
    Clase(const Clase& other) = delete;
```
Sin embargo, si alguien de verdad quiere copiar la clase puede usar memcpy y copiarla bit a bit, "haciendo trampa". Sin embargo eso puede tener comportamientos indefinidos.

## Que es la Standar Template Library (STL)? Que ventajas ofrece? Ejemplifique
La STL es un conjunto de utilidades, algoritmos, y containters que ofrece C++, estas ayudas estan muy buenas para ahorrarse tiempo al momento de programar, y algo muy bueno que tiene es que esta hecha para que sea compatible entre si misma sin importar la clase que le pongas en el template, como por ejemplo, todos los containers pueden tener iteradores que funcionan de la misma manera, y se obtienen de la misma manera (.begin(), .end()).
```c++
int main (int argc, char** argv) {
    std::list<int> unaLista(); //supongamos que tiene muchos numeros
    std::vector<int> unVector(); //supongamos tiene los mismos numeros que la lista
    if (std::min(unaLista) == std::min(unVector)) {
        std::cout << "Hola!" << std::endl;
    }
    return 0;
}
```

## Escriba una rutina que dibuje un rombo amarillo, centrado, de la mitad de tamanio de la ventana
