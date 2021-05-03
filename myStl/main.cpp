#include "Vector/Vector.h"
#include "List/List.h"
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

void list_test() {
    List<int> list;
    auto it1 = list.push_back(0);
    auto it = list.push_back(1);
    std::cout << list << '\n';
    list.push_back(2);
    list.push_back(4);
    auto it2 = list.push_back(3);
    std::cout << list << '\n';

    list.erase(it);
    std::cout << list << '\n';
    list.erase(it1);
    std::cout << list << '\n';
    list.erase(it2);
    std::cout << list << '\n';
    it = list.push_back(5);
    list.push_back(6);
    std::cout << list << '\n';
    list.insert(3, it);
    std::cout << list << '\n';
    list.insert(0, list.begin());
    std::cout << list << '\n';
}

int main() {
    list_test();
    
    return 0;
}