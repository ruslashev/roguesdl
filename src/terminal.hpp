#ifndef TERMINAL_HPP
#define TERMINAL_HPP
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <string>

// Imitates an emulator

class Terminal
{
private:
	TTF_Font *font;
public:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event events;
	SDL_Texture *fontText;

	Terminal(std::string title, int columns, int rows, \
		std::string fontPath, int fontSize);
	~Terminal();

	bool loadFont(std::string fontPath, int fontSize);

	void draw();
	void quit();
};

#endif
