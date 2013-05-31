#include "terminal.hpp"

void fatal(int code, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);

	exit(code);
}

Terminal::Terminal(std::string title, int columns, int rows, \
		std::string fontPath, int fontSize)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		fatal(1, "Failed to Initialize SDL: \"%s\"\n", SDL_GetError()); 

	if (TTF_Init() == -1)
		fatal(1, "Failed to Initialize SDL_ttf: \"%s\"\n", TTF_GetError());

	SDL_Window *window = SDL_CreateWindow("Hello World!\n", \
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,\
			SDL_WINDOW_SHOWN);
	if (window == NULL)
		fatal(2, "Failed to open a window: \"%s\"\n", SDL_GetError());

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | \
			SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
		fatal(2, "Failed to initialize a renderer: \"%s\"\n", SDL_GetError());

	loadFont(fontPath, fontSize);
}

void Terminal::loadFont(std::string fontPath, int fontSize)
{
	font = TTF_OpenFont("SourceCodePro-Regular.otf", 13);
	if (font == NULL)
		fatal(3, "Failed to load font: %s\n", TTF_GetError());

	TTF_SetFontHinting(font, TTF_HINTING_LIGHT);
	SDL_Surface *fontSurf = TTF_RenderText_Shaded(font, "beep boop woof", \
			{255, 255, 255}, {30, 30, 30});
	fontText = SDL_CreateTextureFromSurface(renderer, fontSurf);
	SDL_FreeSurface(fontSurf);
	TTF_CloseFont(font);
}

Terminal::~Terminal()
{
	SDL_DestroyTexture(fontText);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();

	SDL_Quit();
}
