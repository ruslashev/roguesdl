#ifndef TERMINAL_HPP
#define TERMINAL_HPP
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <string>
#include <vector>
#include <new>

// Imitates an emulator


// struct Cell // sometime later
// {
// 	unsigned char ch;
// 	// SDL_Color color;
// 	// bool bold;
// };

class Terminal
{
private:
	TTF_Font *font;

	unsigned short cursX = 0, cursY = 0;
	std::vector<std::vector<char>> screen;
public:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	int rows, columns;

	Terminal(const char* title, int columns, int rows, const char* fontPath, \
			int fontSize);
	~Terminal();

	void RebuildSurface();
	void Draw();

	void move(int y, int x);
	void addch(char c);
	void addstr(std::string str);
	void mvaddch(int y, int x, char c);
	void mvaddstr(int y, int x, std::string str);

	void clear();

	std::string getch();
	SDL_Keysym* getkey();
	// std::string getkeyv();
};

#endif
