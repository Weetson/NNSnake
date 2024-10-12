#include "GeneticAlgorithm.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

GeneticAlgorithm::GeneticAlgorithm(int population_size, int input_size, int hidden_size, int output_size) {
    srand(time(0));
    population = std::vector<NeuralNetwork>(population_size, NeuralNetwork(input_size, hidden_size, output_size));
    fitness_scores = std::vector<float>(population_size, 0.0);
}

void GeneticAlgorithm::calculate_fitness() {
    // Example fitness calculation, replace with actual game logic
    for (int i = 0; i < population.size(); ++i) {
        fitness_scores[i] = rand() % 100; // Replace with actual game score
    }
}

NeuralNetwork GeneticAlgorithm::crossover(const NeuralNetwork &parent1, const NeuralNetwork &parent2) {
    // Simple crossover implementation, replace with your own
    NeuralNetwork child = parent1;

    // Swap some weights
    for (int i = 0; i < parent1.weights_input_hidden.size(); ++i) {
        for (int j = 0; j < parent1.weights_input_hidden[i].size(); ++j) {
            if (rand() % 2 == 0) {
                child.weights_input_hidden[i][j] = parent2.weights_input_hidden[i][j];
            }
        }
    }

    for (int i = 0; i < parent1.weights_hidden_output.size(); ++i) {
        for (int j = 0; j < parent1.weights_hidden_output[i].size(); ++j) {
            if (rand() % 2 == 0) {
                child.weights_hidden_output[i][j] = parent2.weights_hidden_output[i][j];
            }
        }
    }

    return child;
}

void GeneticAlgorithm::mutate_population() {
    for (auto &network : population) {
        network.mutate();
    }
}

void GeneticAlgorithm::evolve() {
    calculate_fitness();
    std::vector<NeuralNetwork> new_population;

    for (int i = 0; i < population.size(); ++i) {
        NeuralNetwork parent1 = population[rand() % population.size()];
        NeuralNetwork parent2 = population[rand() % population.size()];

        NeuralNetwork child = crossover(parent1, parent2);
        new_population.push_back(child);
    }

    population = new_population;
    mutate_population();
}

NeuralNetwork GeneticAlgorithm::get_best_network() {
    calculate_fitness();
    int best_index = std::max_element(fitness_scores.begin(), fitness_scores.end()) - fitness_scores.begin();
    return population[best_index];
}

