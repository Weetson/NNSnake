#include <iostream>
#include "Snake.h"

using namespace std;

Snake::Snake(int x, int y) {
	coordinates = {{x, y}};
	last_direction = 'R';
}

void Snake::update(vector<vector<int>> &coordinates) {
	// Проверим текущие координаты головы
	vector<int> head = coordinates[0];
	int new_x = head[0];
	int new_y = head[1];

	// Обновим координаты головы
	switch(last_direction) {
		case 'R':
			new_x += 1;
			break;
		case 'L':
			new_x -= 1;
			break;
		case 'U':
			new_y -= 1;
			break;
		case 'D':
			new_y += 1;
			break;
		default:
			cout << "Error";
	}

	// Проверим, что голова не выходит за пределы массива
	if (new_x < 0 || new_y < 0 || new_x >= coordinates.size() || new_y >= coordinates[0].size()) {
		cout << "Snake head out of bounds!" << endl;
		return;
	}

	// Обновим координаты тела
	if (coordinates.size() > 1) {
		for (int i = coordinates.size() - 1; i > 0; i--) {
			coordinates[i] = coordinates[i - 1];
		}
	}

	// Установим новые координаты головы
	coordinates[0][0] = new_x;
	coordinates[0][1] = new_y;
}

void Snake::reset(int x, int y) {
	coordinates = {{x, y}};
	last_direction = 'R';
}
