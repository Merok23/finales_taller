/**
4. Declare la clase Fracción para almacenar una fracción (numerador/denominador), considerando:
- Atributos que considere necesarios
- Accesibilidad a la Clase
- Incluir los operadores *, ++ (post-incremento), ++(pre-incremento),
 >> (impresión), << (carga desde consola), float
*/
#include <iostream>

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
