#include <iostream>
#include <thread>

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
