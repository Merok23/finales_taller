#include <iostream>

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