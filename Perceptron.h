//
// Created by janek on 5/17/2024.
//

#ifndef CNN_PERCEPTRON_H
#define CNN_PERCEPTRON_H

#include <vector>

class Perceptron {
public:
    explicit Perceptron(int inputsSize);
    void getOutSideInputs();
    float getOutput();
    void twoWayLink(std::vector<Perceptron*> *preds);
    int getSucIndex() const;
    void setPredacessors(const std::vector<Perceptron *> &predacessors);
    void setSuccessors(const std::vector<Perceptron *> &successors);
    void initWeights();
    void setInputs(std::vector<float>& inputs);

    [[nodiscard]] const std::vector<Perceptron *> &getSuccessors() const;
    [[nodiscard]] const std::vector<Perceptron *> &getPredacessors() const;
    [[nodiscard]] std::vector<float> *getInputs() const;
    [[nodiscard]] std::vector<float> *getWeights() const;

    void setInputs(std::vector<float> *inputs);

private:
    void addSuccessor(Perceptron *perceptron, int index);
    int sucIndex; /*TODO rename*/
    std::vector<Perceptron*> predacessors;
    std::vector<Perceptron*> successors;
    std::vector<float>* inputs;
    std::vector<float>* weights;

public:
    static int objectCounter;   /*TODO delete these 2 counters as they are only used for testing purposes*/
    static int connectionCounter;
};


#endif //CNN_PERCEPTRON_H
