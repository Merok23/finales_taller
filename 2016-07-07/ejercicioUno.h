/*
##  Declare una clase Fecha para encapsular una fecha. Incluya al menos: 
- Constructor default (fecha de hoy), 
- Constructor con valor de inicialización (int día, int mes, int año)
- Constructor de Copia; 
- Operador <, 
- Operador ==, 
- Operador =, 
- Operador int (que devuelva los días entre 01/01/1970 y la fecha almacenada)
*/

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