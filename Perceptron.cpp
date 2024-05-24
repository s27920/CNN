//
// Created by janek on 5/17/2024.
//

#include "Perceptron.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <random>



int Perceptron::objectCounter = 0;
int Perceptron::connectionCounter = 0;

Perceptron::Perceptron(int inputsSize) {
    inputs->resize(inputsSize);
    weights->resize(inputsSize);
    sucIndex = 0;
    objectCounter++;
}

void Perceptron::getOutSideInputs() {
    if (predacessors->empty()) {
        //TODO remember to clean this up
        auto* outputs = new std::vector<float>(inputs->size());
        for (int i = 0; i < inputs->size(); i++) {
            outputs->at(i) = predacessors->at(i)->getOutput();
        }
        inputs = outputs;
    }
}

float Perceptron::getOutput() {
    float sum = 0.0f;
    for (int i = 0; i < inputs->size(); i++) {
        sum += inputs->at(i) * weights->at(i);
    }
    return 1 / (1 + std::exp(-sum));
}

void Perceptron::twoWayLink(std::vector<Perceptron*> *preds) {
    this->setPredacessors(preds);
    for (int i = 0; i < inputs->size(); i++){
        predacessors->at(i)->addSuccessor(this, predacessors->at(i)->getSucIndex());
        connectionCounter++;
    }
}

void Perceptron::addSuccessor(Perceptron *perceptron, int index) {
    successors->at(index) = perceptron;
    sucIndex++;
}

void Perceptron::initWeights() {
    size_t predCount = 1;
    if(!predacessors->empty()){
        predCount = predacessors->size();
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    double stdDev = std::sqrt(2.0 / (predacessors->size() + successors->size()));
    std::normal_distribution<> d(0,stdDev);
    for (int i = 0; i < predCount; i++){
        weights->at(i) = d(gen);
    }
}

int Perceptron::getSucIndex() const {
    return sucIndex;
}



const std::vector<Perceptron *> *Perceptron::getSuccessors() const {
    return successors;
}

const std::vector<Perceptron *> *Perceptron::getPredacessors() const {
    return predacessors;
}

void Perceptron::setInputs(std::vector<float> *inputs) {
    Perceptron::inputs = inputs;
}

std::vector<float> *Perceptron::getInputs() const {
    return inputs;
}

std::vector<float> *Perceptron::getWeights() const {
    return weights;
}

void Perceptron::setPredacessors(std::vector<Perceptron *> *predacessors) {
    Perceptron::predacessors = predacessors;
}

void Perceptron::setSuccessors(std::vector<Perceptron *> *successors) {
    Perceptron::successors = successors;
}


