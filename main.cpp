#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Snake.h"
#include <ncurses.h>

using namespace std;

void apple(vector<int> field_sizes, vector<int> &apple_cords) {
	apple_cords[0] = rand() % field_sizes[0];
	apple_cords[1] = rand() % field_sizes[1];
}

int main() {
	vector<int> field_size = {25, 19};
	vector<int> apple_cords = {0, 0};
	Snake snake(6, 7);

	apple(field_size, apple_cords);

	// ncurses init
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	nodelay(stdscr, TRUE);

	int ch;

	while (true) {
		// Keyboard check
		ch = getch();
		switch (ch) {
			case KEY_UP:
				if (snake.last_direction != 'D') snake.last_direction = 'U';
				break;
			case KEY_DOWN:
				if (snake.last_direction != 'U') snake.last_direction = 'D';
				break;
			case KEY_LEFT:
				if (snake.last_direction != 'R') snake.last_direction = 'L';
				break;
			case KEY_RIGHT:
				if (snake.last_direction != 'L') snake.last_direction = 'R';
				break;
			case 'q':
				endwin();
				return 0;
		}

		// Snake update
		snake.update(snake.coordinates);

		// Clear window
		clear();

		// Upper border
		printw("\n\n\n\n");
		for (int i = 0; i < field_size[0] + 2; i++) { printw("#"); }
		printw("\n");

		// Main logic
		for (int i = 0; i < field_size[1]; i++) {
			printw("#");
			for (int j = 0; j < field_size[0]; j++) {
				bool isSnakePart = false;
				for (vector<int> s : snake.coordinates) {
					if (s[0] == j && s[1] == i) {
						printw("0");
						isSnakePart = true;
						break;
					}
				}
				if (!isSnakePart) {
					if (apple_cords[0] == j && apple_cords[1] == i) {
						printw("@");
					} else {
						printw(".");
					}
				}
			}
			printw("#\n");
		}

		// Lower border
		for (int i = 0; i < field_size[0] + 2; i++) { printw("#"); }
		printw("\n");

		// Snake on borders check
		vector<int> head = snake.coordinates[0];
		if (head[0] < 0 || head[1] < 0 || head[0] >= field_size[0] || head[1] >= field_size[1]) {
			clear();
			printw("You lose!!! Looser!!!");
			refresh();
			napms(2000); // Wait for 2 seconds before exiting
			endwin();
			return 0;
		}

		// Check apple
		if (head[0] == apple_cords[0] && head[1] == apple_cords[1]) {
			snake.coordinates.push_back(snake.coordinates.back());
			apple(field_size, apple_cords);
		}

		// Check on snake eat itself
		if(snake.coordinates.size() > 4) {
			for (int i = 1; i < snake.coordinates.size(); i++) {
				if(snake.coordinates[i] == snake.coordinates[0]) {
					clear();
					printw("You lose!!! Looser!!!");
					refresh();
					napms(2000); // Wait for 2 seconds before exiting
					endwin();
					return 0;
				}
			}
		}

		// Update screen
		printw("\nSize = %d", (int)snake.coordinates.size());
		refresh();
		napms(220);
	}

	endwin();
	return 0;
}
