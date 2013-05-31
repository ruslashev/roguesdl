#include "terminal.hpp"

Terminal::Terminal(std::string title, int columns, int rows, \
		std::string fontPath, int fontSize)
{
	// Initializing SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		fprintf(stderr, "Failed to Initialize SDL: \"%s\"\n", \
				SDL_GetError());
	}
	// Initializing SDL_ttf
	if (TTF_Init() == -1)
	{
		fprintf(stderr, "Failed to Initialize SDL_ttf: \"%s\"\n", \
				TTF_GetError());
		exit(1);
	}
	// Opening a window
	SDL_Window *window = SDL_CreateWindow("Hello World!\n", \
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,\
			SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		fprintf(stderr, "Failed to open a window: \"%s\"\n", SDL_GetError());
		exit(2);
	}
	// Initializing a renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | \
			SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		fprintf(stderr, "Failed to initialize a renderer: \"%s\"\n", SDL_GetError());
		exit(2);
	}
	// Loading a font
	if (!loadFont(fontPath, fontSize))
		exit(3);
}

bool Terminal::loadFont(std::string fontPath, int fontSize)
{
	font = TTF_OpenFont("SourceCodePro-Regular.otf", 13);
	if (font == NULL)
	{
		fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
		return false;
	}
	TTF_SetFontHinting(font, TTF_HINTING_LIGHT);
	SDL_Surface *fontSurf = TTF_RenderText_Shaded(font, "beep boop woof", {255, 255, 255}, {0, 0, 0});
	fontText = SDL_CreateTextureFromSurface(renderer, fontSurf);
	SDL_FreeSurface(fontSurf);
	TTF_CloseFont(font);

	return true;
}

Terminal::~Terminal()
{
	SDL_DestroyTexture(fontText);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();

	SDL_Quit();
}
