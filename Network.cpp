//
// Created by janek on 5/17/2024.
//

#include "Network.h"
#include "Perceptron.h"
#include <iostream>
#include <cstdlib>
#include <limits>


Network::Network(std::vector<int> &structure) {
    std::vector<std::vector<Perceptron*>*> edges = this->createNetwork(structure);
    initLayer = edges.at(0);
    terminalLayer = edges.at(1);
}

Network::~Network() {
//TODO propagate the network and clean it up. no memory leaks for you >:(
}

std::vector<std::vector<Perceptron*>*> Network::createNetwork(std::vector<int> &structure) {
    size_t initLayerSize = structure.at(0);
    size_t sucSize = structure.at(1);
    auto *initLayerCreated = new std::vector<Perceptron*>(initLayerSize);
    for (size_t i = 0; i < initLayerSize; i++){
        auto *perceptron = new Perceptron(1);
        perceptron->setSuccessors(std::vector<Perceptron*>(sucSize));
        perceptron->initWeights();
        initLayerCreated->at(i) = perceptron;
    }
    std::vector<Perceptron *> *terminalLayerCreated = hiddenLayers(structure, initLayerCreated);

    std::vector<std::vector<Perceptron*>*> edges;
    edges.resize(2);
    edges.at(0) = initLayerCreated;
    edges.at(1) = terminalLayerCreated;
    return edges;
}

std::vector<Perceptron *> * Network::hiddenLayers(std::vector<int> &structure, std::vector<Perceptron *> *previousLayer) {
    for (int i = 1; i < structure.size(); i++){
        auto * currLayer = new std::vector<Perceptron*>(structure.at(i));
        int inputsSize = structure.at(i-1);/*inputsSize is equal to the amount of predecessors a Perceptron has*/
        for (int j = 0; j < structure.at(i); j++){
            auto *perceptron = new Perceptron(inputsSize);
            perceptron->setPredacessors(std::vector<Perceptron*> (inputsSize));
            if(i+1 < structure.size()){
                std::vector<Perceptron*> successors(structure.at(i+1));
                perceptron->setSuccessors(successors);
            }
            perceptron->twoWayLink(previousLayer);
            perceptron->initWeights();
            currLayer->at(j) = perceptron;
        }
        if (i != 1){
            delete previousLayer;
        }
        previousLayer = currLayer;
        if (i == structure.size()-1){
            return currLayer;
        }
    }
    return previousLayer;
}

void Network::getActivations(Image imageToClassify) {
    const std::vector<int>* pixelVector = imageToClassify.getPixelVector();
    for (int i = 0; i < initLayer->size(); i ++){
        initLayer->at(i)->setInputs(std::vector<float>() = {(pixelVector->at(i) & 0xFF)/255.0f});
    }
    std::vector<Perceptron*>* currLayer = initLayer;
    for(;; currLayer = currLayer->at(0)->getSuccessors()){
        size_t currSize = currLayer.size();
        for (size_t i = 0; i < currSize; i++){
            currLayer.at(i)->getOutSideInputs();
        }
        if (currLayer.at(0)->getSuccessors().empty()){
            break;
        }
    }
    size_t currSize = currLayer.size();
    std::vector<float> activations = std::vector<float>(currSize);
    for (size_t i = 0; i < currSize; i++){
        activations.at(i) = currLayer.at(i)->getOutput();
    }
    this->activations = activations;
}

void Network::backProp() {
    //start of terminal layer
    std::vector<Perceptron*>* currLayer = terminalLayer;
    size_t currLayerSize = currLayer.size();
    std::vector<float> sucErrorGradientVector = std::vector<float>(currLayerSize);
    size_t currentGuess = decodeActivations();
    for (size_t i = 0; i < currLayerSize; i++){
        std::vector<float>* weights = currLayer.at(i)->getWeights();
        std::vector<float>* inputs = currLayer.at(i)->getInputs();
        size_t inLength = weights->size();

        float output = currLayer.at(i)->getOutput();
        float error = (this->image->checkLabel((int)currentGuess) - output);
        float errorGradient = (error * ((1-output)*output));
        for (size_t j = 0; j < inLength; j++) {
            weights->at(j) += learningRate * errorGradient * inputs->at(j);
        }
        sucErrorGradientVector.at(i) = errorGradient;
    }
    //end of terminal layer
    //start of hidden layers
    currLayer = currLayer.at(0)->getPredacessors();
}

size_t Network::decodeActivations() {
    size_t activationsSize = this->activations.size();
    float max = -std::numeric_limits<float>::infinity();
    size_t maxIndex = -1;
    for (size_t i = 0; i < activationsSize; i++){
        float activationI = this->activations.at(i);
        if (activationI > max){
            max = activationI;
            maxIndex = i;
        }
    }
    return maxIndex;
}
