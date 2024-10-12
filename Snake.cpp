#include <iostream>
#include "Snake.h"

using namespace std;

Snake::Snake(int x, int y) {
	coordinates = {{x, y}};
	last_direction = 'R';
}

void Snake::update(vector<vector<int>> &coordinates) {

	// Move body
	if (coordinates.size() > 1) {

		for (int i = coordinates.size() - 1; i > 0; i--) {
			coordinates[i] = coordinates[i - 1];
		}
	}
	// Move head
	switch(last_direction) {
		case 'R':
			coordinates[0][0] += 1;
			break;
		case 'L':
			coordinates[0][0] -= 1;
			break;
		case 'U':
			coordinates[0][1] -= 1;
			break;
		case 'D':
			coordinates[0][1] += 1;
			break;
		default:
			cout << "Nigger";
	}
	

}
