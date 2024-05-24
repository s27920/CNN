//
// Created by janek on 5/17/2024.
//

#ifndef CNN_NETWORK_H
#define CNN_NETWORK_H

#include "Perceptron.h"
#include "Image.h"
#include <vector>

class Network {
private:
//    TODO implement dynamic learning rate this is temporary
    float learningRate = 0.2;
    Image* image;
    std::vector<float> activations;
    std::vector<Perceptron*> initLayer;
    std::vector<Perceptron*> terminalLayer;
    std::vector<Perceptron *> * hiddenLayers(std::vector<int> &structure, std::vector<Perceptron *> *previousLayer);
    void backProp();
    size_t decodeActivations();

public:

    Network(std::vector<int> &structure);
    std::vector<std::vector<Perceptron*>*> createNetwork(std::vector<int> &structure);
    void getActivations(Image imageToClassify);
    ~Network();
};


#endif //CNN_NETWORK_H
