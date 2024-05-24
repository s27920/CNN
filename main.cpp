#include <iostream>
#include "Network.h"

int main() {
    std::vector<int> vec = {784, 16, 16, 10};
    auto* n = new Network(vec);
    std::cout << "Hello, World!" << std::endl;
    std::cout<< "Neurons in network " << Perceptron::objectCounter << std::endl;
    std::cout<< "Connections in network " << Perceptron::connectionCounter << std::endl;
    return 0;
}
