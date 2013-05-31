#include "terminal.hpp"

void fatal(int code, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	fprintf(stderr, "%sERROR%s ", "\e[31m", "\e[0m");
	vfprintf(stderr, format, args);
	va_end(args);

	exit(code);
}

Terminal::Terminal(const char* title, int columns, int rows, \
		const char* fontPath, int fontSize)
{
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
			fatal(1, "Failed to Initialize SDL: %s\n", SDL_GetError());

		if (TTF_Init() == -1)
			fatal(1, "Failed to Initialize SDL_ttf: %s\n", TTF_GetError());
	}

	font = TTF_OpenFont(fontPath, fontSize);
	if (font == NULL)
		fatal(3, "%s\n", TTF_GetError()); // -> "Couldn't open Blah.otf"

	// TODO
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, \
			SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	if (window == NULL)
		fatal(2, "Failed to open a window: %s\n", SDL_GetError());

	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | \
				SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL)
			fatal(2, "Failed to initialize a renderer: %s\n", SDL_GetError());
	}

	TTF_SetFontHinting(font, TTF_HINTING_LIGHT);
	SDL_Surface *fontSurf = TTF_RenderText_Shaded(font, "beep boop woof", \
											{255, 255, 255}, {30, 30, 30});
	fontText = SDL_CreateTextureFromSurface(renderer, fontSurf);
	SDL_FreeSurface(fontSurf);
	TTF_CloseFont(font);

	screen.resize(columns);
	for (int x = 0; x < columns; x++)
		screen[x].resize(rows);

	for (int x = 0; x < columns; x++)
		for (int y = 0; y < rows; y++)
			screen[x][y] = {'0'};

}

Terminal::~Terminal()
{
	SDL_DestroyTexture(fontText);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();

	SDL_Quit();
}
