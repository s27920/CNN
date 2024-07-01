#include <iostream>
#include "Network.h"

int main() {
    auto* n = new Network(std::vector<int>()={784, 16, 16, 10});
    std::cout<< "Neurons in network " << Perceptron::objectCounter << std::endl;
    std::cout<< "Connections in network " << Perceptron::connectionCounter << std::endl;
    return 0;
}
