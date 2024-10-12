#include "NeuralNetwork.h"
#include <cmath>
#include <cstdlib>

NeuralNetwork::NeuralNetwork(int input_size, int hidden_size, int output_size) {
    weights_input_hidden = std::vector<std::vector<float>>(input_size, std::vector<float>(hidden_size));
    weights_hidden_output = std::vector<std::vector<float>>(hidden_size, std::vector<float>(output_size));

    for (int i = 0; i < input_size; ++i) {
        for (int j = 0; j < hidden_size; ++j) {
            weights_input_hidden[i][j] = random_weight();
        }
    }

    for (int i = 0; i < hidden_size; ++i) {
        for (int j = 0; j < output_size; ++j) {
            weights_hidden_output[i][j] = random_weight();
        }
    }
}

std::vector<float> NeuralNetwork::predict(std::vector<float> &inputs) {
    std::vector<float> hidden(inputs.size(), 0);
    std::vector<float> outputs(hidden.size(), 0);

    for (int i = 0; i < weights_input_hidden.size(); ++i) {
        for (int j = 0; j < weights_input_hidden[i].size(); ++j) {
            hidden[j] += inputs[i] * weights_input_hidden[i][j];
        }
    }

    for (float &value : hidden) {
        value = sigmoid(value);
    }

    for (int i = 0; i < weights_hidden_output.size(); ++i) {
        for (int j = 0; j < weights_hidden_output[i].size(); ++j) {
            outputs[j] += hidden[i] * weights_hidden_output[i][j];
        }
    }

    for (float &value : outputs) {
        value = sigmoid(value);
    }

    return outputs;
}

void NeuralNetwork::mutate() {
    // Example mutation implementation
    for (auto &row : weights_input_hidden) {
        for (float &value : row) {
            if ((rand() % 100) / 100.0 < 0.1) {
                value += random_weight() * 0.1;
            }
        }
    }

    for (auto &row : weights_hidden_output) {
        for (float &value : row) {
            if ((rand() % 100) / 100.0 < 0.1) {
                value += random_weight() * 0.1;
            }
        }
    }
}

float NeuralNetwork::sigmoid(float x) {
    return 1.0 / (1.0 + exp(-x));
}

float NeuralNetwork::random_weight() {
    return ((rand() % 200) / 100.0) - 1;
}

