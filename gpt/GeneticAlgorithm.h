#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "NeuralNetwork.h"
#include <vector>

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int population_size, int input_size, int hidden_size, int output_size);
    void evolve();
    NeuralNetwork get_best_network();

private:
    std::vector<NeuralNetwork> population;
    std::vector<float> fitness_scores;
    void calculate_fitness();
    NeuralNetwork crossover(const NeuralNetwork &parent1, const NeuralNetwork &parent2);
    void mutate_population();
};

#endif

