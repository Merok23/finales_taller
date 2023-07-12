/*
Implemente una función C++ denominada DobleSiNo que reciba dos listas de elementos y devuelva una nueva lista  
duplicando   los   elementos   de   la   primera   que   no   están   en   la segunda:
               std::list<T> DobleSiNo(std::list<T> a,std::list<T> b);
*/

#include <stdlib.h>
#include <iostream>
#include <list>

std::list<int> dobleSiNo(std::list<int> a,std::list<int> b) {
    bool found = false;
    std::list<int> elementsNotFound;
    for (auto&& elementA : a) {
        for (auto&& elementB : b) {
            if (elementA == elementB) {
                found = true;
                break;
            }
        }
        if (!found) elementsNotFound.push_back(elementA);
        found = false;
    }
    for (auto&& element : elementsNotFound) {
        a.push_back(element);
    }
    return a;
}



int main (int argc, char** argv) {
    std::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::list<int> b = {1, 3, 5, 7, 9};
    std::list<int> result = dobleSiNo(a, b);
    for (auto&& res : result) {
        std::cout << res << " ";
    }
    std::cout << std::endl;
    return 0;
}