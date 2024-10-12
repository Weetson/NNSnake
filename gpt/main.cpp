#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ncurses.h>
#include <algorithm> // добавим этот include
#include "Snake.h"
#include "NeuralNetwork.h"
#include "GeneticAlgorithm.h"

using namespace std;

void apple(vector<int> field_sizes, vector<int> &apple_cords) {
	apple_cords[0] = rand() % field_sizes[0];
	apple_cords[1] = rand() % field_sizes[1];
}

int main() {
	vector<int> field_size = {25, 19};
	vector<int> apple_cords = {0, 0};
	Snake snake(6, 7);
	GeneticAlgorithm ga(50, 6, 8, 4);

	apple(field_size, apple_cords);

	// ncurses init
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	nodelay(stdscr, TRUE);

	int generation = 0;
	while (true) {
		clear();

		// Get the best network from the current population
		NeuralNetwork best_network = ga.get_best_network();

		// Simulate the snake game
		snake.reset(6, 7);
		apple(field_size, apple_cords);

		while (true) {
			// Get inputs for the neural network
			vector<float> inputs = { (float)snake.coordinates[0][0] / field_size[0], (float)snake.coordinates[0][1] / field_size[1],
				(float)apple_cords[0] / field_size[0], (float)apple_cords[1] / field_size[1],
				(float)field_size[0], (float)field_size[1] };

				// Get the outputs from the neural network
				vector<float> outputs = best_network.predict(inputs);

				// Determine the action
				int action = distance(outputs.begin(), max_element(outputs.begin(), outputs.end()));

				// Update the snake's direction based on the action
				switch(action) {
					case 0: snake.last_direction = 'U'; break;
					case 1: snake.last_direction = 'D'; break;
					case 2: snake.last_direction = 'L'; break;
					case 3: snake.last_direction = 'R'; break;
				}

				// Snake update
				snake.update(snake.coordinates);

				// Check for collisions
				for (vector<int> s : snake.coordinates) {
					if (s[0] < 0 || s[1] < 0 || s[0] >= field_size[0] || s[1] >= field_size[1]) {
						clear();
						printw("You lose!!! Looser!!!\n");
						refresh();
						napms(1000); // пауза перед выходом
						endwin();
						return 0;
					}
				}

				// Check for apple
				if (snake.coordinates[0][0] == apple_cords[0] && snake.coordinates[0][1] == apple_cords[1]) {
					snake.coordinates.push_back(snake.coordinates[0]);
					apple(field_size, apple_cords);
				}

				// Clear window
				clear();

				// Draw upper border
				printw("\n\n\n\n");
				for (int i = 0; i < field_size[0] + 2; i++) printw("#");
				printw("\n");

			// Draw field
			for (int i = 0; i < field_size[1]; i++) {
				printw("#");
				for (int j = 0; j < field_size[0]; j++) {
					if (apple_cords[0] == j && apple_cords[1] == i) {
						printw("@");
					} else {
						bool is_snake = false;
						for (vector<int> s : snake.coordinates) {
							if (s[0] == j && s[1] == i) {
								printw("0");
								is_snake = true;
								break;
							}
						}
						if (!is_snake) printw(".");
					}
				}
				printw("#\n");
			}

			// Draw lower border
			for (int i = 0; i < field_size[0] + 2; i++) printw("#");

			refresh();
			napms(100);
		}

		ga.evolve();
		generation++;
	}

	endwin();
	return 0;
}
