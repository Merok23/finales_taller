#include <thread>
#include <mutex>
#include <iostream>

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