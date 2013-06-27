#ifndef WORLD_HPP
#define WORLD_HPP
#include <vector>

class World
{
public:
	std::vector<std::vector<char>> map;
	int width, height;

	World(int newWidth, int newHeight);
};

#endif
