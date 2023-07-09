## 1. Declare una clase Fecha para encapsular una fecha. Incluya al menos: 
- Constructor default (fecha de hoy), 
- Constructor con valor de inicialización (int día, int mes, int año)
- Constructor de Copia; 
- Operador <, 
- Operador ==, 
- Operador =, 
- Operador int (que devuelva los días entre 01/01/1970 y la fecha almacenada)
```c++
class Date {
    private:
        int day;
        int month;
        int year;
    public:
        Date();
        Date(int day, int month, int year);
        Date(const Date &other);
        bool operator<(const Date &other) const;
        bool operator==(const Date &other) const;
        Date& operator=(const Date &other);
        operator int() const;
};
```
## 2. ¿Cual es el motivo por el cual las bibliotecas que incluyen templates deben distribuirse con el código fuente?

Deben distribuirse con el codigo fuente debido a que para que el template funcione, el compilador compila el codigo fuente con el tipo correspondiente en momento de compilación, y eso lo hace con el código fuente y no lo puede hacer con el binario compilado.

## 3. Describa las formas en las cuales un thread puede finalizar su ejecución. Ejemplifique.

La forma mas común es que el hilo retorne y se lo espere con un join() para liberar sus recursos:

```c++
void threadFunc() {
    //thread stuff
}

int main (int argc, char** argv) {
    std::thread t1(threadFunc);
    t1.join();
    return 0;
}
```
Un hilo tambien puede finalizar de forma inesperada (o esperada) tirando una excepción.

```c++
void threadFunc() {
    //thread stuff
    std::throw std::exception("Everything broke up");
}

int main (int argc, char** argv) {
    try{
        std::thread t1(threadFunc);
        t1.join(); //will never reach here
        return 0;
    }catch(const std::exception &e) {
        return 1;
    }
}
```

## 4. ¿Qué es una MACRO de C? Ejemplifiqué.

Una macro de C funciona igual que una macro de assembly, se puede utilizar para reemplazar codigo en el momento de compilación, por ejemplo: 
```c
#define SUMAR(a, b) ((a) + (b))
...
int a = 20;
int b = 30
return SUMAR(a, b)
...
```

## 5. Escriba una rutina (para ambiente gráfico Windows o Linux) que tome el contenido de un edit y ponga la primera letra de cada palabra de su contenido en mayúsculas.

