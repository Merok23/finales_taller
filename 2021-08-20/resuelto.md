## 1. Describa con exactitud las siguientes declaraciones/definiciones globales:
- static signed char *(*A)();
- extern unsigned long *(*C)[1];
- char *B(){return NULL;}

1. static signed char* (*A)()
A es un puntero de funcion que no recibe parametros y que devuelve un puntero de caracter con signo, y tiene el modificador static que hace que solo pueda ser utilizada en el archivo en el que esta.
2. extern unsigned long *(*C)[1];
\*C es un array de longitud 1 de punteros de unsigned long, por lo cual, C es un unsigned long \*\*\*C. (puntero a un array de punteros unsigned long).
3. char*B(){return NULL;}
B es una funcion que devuelve un puntero a char puesto en NULL.

## 2. Escriba una rutina que tome el contenido de un edit (ej.: “hola MUNDO”), pase a Camel (osea, primera letra de cada palabra en mayúscula y todo el resto en minúscula) (ej.: “Hola Mundo”) y lo vuelva a guardar en el mismo edit.
Mucho agua en qt..:
```c++
void camelCase(std::string &unString) {
    char c = unString[0];
    c = toupper(c);
    unString[0] = c;
    for (int i = 1; i < unString.length(); i++) {
        c = unString[i];
        c = tolower(c);
        unString[i] = c;
    }
} 

void qtEditToCamel(QLineEdit& edit) {
    std::string camelText = edit.toText().toStdString();
    std::stringstream iss(camelText);
    std::string finalString = "";
    std::string word;
    while (iss >> word) {
        camelCase(word);
        finalString += word;
    }
    edit.setText(finalString);
}
```
## 3. Explique qué es un constructor MOVE. Ejemplifique su uso.

Un constructor move es una forma de pasarse una instancia de un objeto sin hacer una copia (el default de C++ es copia), de esta forma se puede transferir el ownership del objeto, es decir, si uno le pasa el ownership a otra funcion, cuando se destruya el stack de esa funcion, el objeto se va de scope, y deja de existir junto a esa funcion. Un posible ejemplo, podria ser pasarse el ownership de una clase socket, que si esta hecha de forma RAII, no hay que preocuparse de que cuando termine cerrar el socket.

```C++
void acceptClients() {
    Socket newClientSocket = this->socket.accept();
    Client newClient(newClientSocket);
    //...
}
```

## 4. Declare la clase Fracción para almacenar una fracción (numerador/denominador), considerando:
- Atributos que considere necesarios
- Accesibilidad a la Clase
- Incluir los operadores *, ++ (post-incremento), ++(pre-incremento), >> (impresión), << (carga desde consola), float

```c++
class Fraction {
    private:
        int numerator;
        int denominator;
    public:
        Fraction(int numerator, int denominator);
        Fraction operator*(const Fraction& other) const;
        Fraction operator++(int); //post
        Fraction& operator++(); //pre
        //getters y setters para << y >>
        void setNumerator(const int& numerator);//copy since we'll make our own copy inside
        void setDenominator(const int& denominator);
        int getNumerator() const;
        int getDenominator() const;
        operator float () const;
};

std::istream& operator>>(std::istream& in, Fraction& frac);
std::ostream& operator<<(std::ostream& out, const Fraction& frac);
```

## 5. Describa el proceso de transformación de código fuente a un ejecutable. Precise las etapas y las tareas desarrolladas en cada una de ellas.
(masomenos)
Primero se fija que este todo escrito y no haya instrucciones que esten mal usadas, es decir, si falta ";s", o si hay algun error del estilo numero = otroNumero +; 
Una vez se confirma que todas las instrucciones son validas, se traducen todas las instrucciones a assembly, haciendose una tabla de simbolos, viendo cuales variables estan definidas en otros archivos, las posiciones relativas en el codigo, etc..
Dependiendo la configuracion que se use del compilador, se va a ir a buscar todas las dependencias (o si es dinamico, se buscan en tiempo de ejecucion).
Una vez se tiene todo, se procede a cambiar las instrucciones a codigo maquina.

## 6. ¿Qué es la STL?¿Qué recursos (funciones, algoritmos, etc.) ofrece?¿Qué ventaja nos da su uso?

La Standard Template Library es un conjunto de recursos que te ofrece la libreria estandar de C++, la idea es que estos recursos al ser usados en templates, estos no dependan de la clase en la que se esta aplicando. Los recursos que te puede ofrecer la libreria son:
- Containers:
List, map, unorderedmap, vector, etc...
- Algoritmos:
remove_if, sort, find, etc..
- utilidades:
shared_ptr, unique_ptr, etc..

Las ventajas de usar esta libreria es que te podes abstraer mucho, y concentrarte en los problemas de verdad, tenes la tranquilidad de que por ejemplo, sort, funciona siempre, y que si hay un bug, seguro es en tu codigo.

## 7. Escriba un programa que reciba por línea de comandos un Puerto y una IP. El programa debe conectarse al destino indicado y quedar en escucha de paquetes con la forma “d..d,d..d,… =”. El programa debe imprimir en stdout el checksum (sumatoria módulo 256) de cada paquete. Cuando se reciba un paquete vacío se debe finalizar ordenadamente.

```c
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
        //lo mismo de siempre, solo cambia la condicion de corte.
    }
    freeaddrinfo(results);
    shutdown(sdf, SHUT_RDWR);
    close(sdf);
    return 0;
}
```

## 8. ¿Cómo se logra que 2 threads accedan (lectura/escritura) a un mismo recurso compartido sin que se generen problemas de consistencia? Ejemplifique.

Con un mutex //ya hice varios ejemplos, mejor hago otras cosas.

## 9. Escribir un programa ISO C MULTIPLATAFORMA que procese el archivo “nros_2bytes_bigend.bin” sobre sí mismo, leyendo los nros (que están grabados en bigendian) y eliminando los número múltiplos de 7.

```c
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
```

## 10. Haciendo uso de tipos básicos de C y punteros, Implemente la función ISO C int Buscar(const char *DondeBusco, const char *QueBusco) que devuelva la cantidad de veces que se encuentra el string QueBusco en el string DondeBusco

```c
int search(const char* string, const char* subString) {
    int len = strlen(string);
    int subLen = strlen(subString);
    int end = subLen;
    int start = 0;
    char buff[subLen + 1];
    int result = 0;
    buff[subLen] = "\0";
    for (int i = 0; i < len - subLen; i++) {
        memcpy(buff, string + start, subLen);
        if (strcmp(buff, subString) == 0) result++;
        end+=1;
        start+=1;
    }
    return result;
}
```