#include "Vector.h"
#include <iostream>


void vector_test() {
    Vector<int> vec;
    vec.push_back(1);
    auto it2 = vec.push_back(2);
    std::cout << vec << '\n';
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(6);
    std::cout << vec << '\n';
    vec.reserve(5);
    vec.push_back(7);
    std::cout << vec << '\n';
    auto it = vec.insert(vec.find(4), 3);
    std::cout << vec << '\n';
    vec.insert(vec.find(4), 3);
    std::cout << vec << '\n';
    vec.insert(vec.find(4), 3);
    std::cout << vec << '\n';
    vec.erase(it);
    std::cout << vec << "Size: " << vec.size() <<'\n';
    vec.erase(it2);
    std::cout << vec << "Size: " << vec.size() << '\n';
}


int main() {
    vector_test();

    return 0;
}