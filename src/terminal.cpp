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

Terminal::Terminal(const char* title, int cols, int rws, \
		const char* fontPath, int fontSize)
{
	columns = cols;
	rows = rws;

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

	screen.resize(columns);
	for (int x = 0; x < columns; x++)
		screen[x].resize(rows);

	for (int x = 0; x < columns; x++)
		for (int y = 0; y < rows; y++)
			screen[x][y] = {'0'};

	RebuildSurface();
}

void Terminal::RebuildSurface()
{
	// TODO optimizing n stuff
	std::string colStr;
	for (int x = 0; x < columns; x++)
	{
		colStr = "";
		for (char &c : screen[x])
			colStr.push_back(c);
		printf("%s\n", colStr.c_str());

		SDL_Surface *fontSurf = TTF_RenderText_Shaded(font, colStr.c_str(), \
				{255, 255, 255}, {30, 30, 30});
		SDL_Rect offsetRect = { 0, fontSurf->h * x, fontSurf->w, fontSurf->h };;
		screenTexture = SDL_CreateTextureFromSurface(renderer, fontSurf);
		SDL_FreeSurface(fontSurf);
		SDL_RenderCopy(renderer, screenTexture, NULL, &offsetRect);
		// TODO &pos -> NULL
	}

	// screenTexture = SDL_CreateTextureFromSurface(renderer, screenSurf);
}

void Terminal::Draw()
{
	// SDL_RenderClear(renderer);


	SDL_RenderPresent(renderer);
}

Terminal::~Terminal()
{
	SDL_DestroyTexture(screenTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);

	TTF_Quit();

	SDL_Quit();
}
