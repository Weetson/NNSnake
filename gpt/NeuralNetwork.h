#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>

class NeuralNetwork {
public:
    NeuralNetwork(int input_size, int hidden_size, int output_size);
    std::vector<float> predict(std::vector<float> &inputs);
    void mutate();
    std::vector<std::vector<float>> weights_input_hidden;
    std::vector<std::vector<float>> weights_hidden_output;
    float sigmoid(float x);
    float random_weight();

private:

};

#endif
