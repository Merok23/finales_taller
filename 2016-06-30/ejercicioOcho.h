/**
8) Declare una clase LongChar para encapsular un carácter en un campo de 16 bits.  
Incluya al menos: Constructor default, con char y Constructor de Copia; Operador <, ==, =, int 
y >>. Implemente el operador >>.
*/
#include <iostream>
#include <string.h>

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
