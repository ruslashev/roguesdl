#ifndef TERMINAL_HPP
#define TERMINAL_HPP
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <string>
#include <vector>
#include <new>

// Imitates an emulator

struct Cell
{
	unsigned char ch;
	// SDL_Color color;
	// bool bold;
};

class Terminal
{
private:
	TTF_Font *font;

	std::vector<std::vector<char>> screen;
public:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event events;
	SDL_Texture *screenTexture;

	int rows, columns;

	Terminal(const char* title, int columns, int rows, const char* fontPath, \
			int fontSize);
	~Terminal();

	void RebuildSurface();
	void Draw();
};

#endif
