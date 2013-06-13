#include "world.hpp"

World::World(int newWidth, int newHeight)
{
	width = newWidth;
	height = newHeight;

	map.resize(height);
	for (int y = 0; y < height; y++)
		map[y].resize(width);

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			map[y][x] = '~';
}

