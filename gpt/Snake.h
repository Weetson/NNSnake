#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <vector>

class Snake {
public:
	Snake(int x, int y);
	std::vector<std::vector<int>> coordinates;
	char last_direction;

	void update(std::vector<std::vector<int>> &coordinates);
	void reset(int x, int y);  // Добавим функцию reset
};

#endif
