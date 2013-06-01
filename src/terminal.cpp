#include "terminal.hpp"

// template<typename T>
// T std::vector<std::vector<T>>::at(int x, int y)
// {
// 	return (*this)[y][x];
// }

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

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		fatal(1, "Failed to Initialize SDL: %s\n", SDL_GetError());

	if (TTF_Init() == -1)
		fatal(1, "Failed to Initialize SDL_ttf: %s\n", TTF_GetError());

	font = TTF_OpenFont(fontPath, fontSize);
	if (font == NULL)
		fatal(3, "%s\n", TTF_GetError());

	int fontWidth;
	TTF_GlyphMetrics(font, '1', NULL, NULL, NULL, NULL, &fontWidth);
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, columns*fontWidth, rows*TTF_FontHeight(font), \
		SDL_WINDOW_SHOWN);
	if (window == NULL)
		fatal(2, "Failed to open a window: %s\n", SDL_GetError());

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | \
			SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
		fatal(2, "Failed to initialize a renderer: %s\n", SDL_GetError());

	TTF_SetFontHinting(font, TTF_HINTING_LIGHT);

	screen.resize(rows);
	for (int y = 0; y < rows; y++)
		screen[y].resize(columns);

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
			screen[y][x] = 'a';

	RebuildSurface();
}

void Terminal::RebuildSurface()
{
	// TODO optimizing n stuff
	std::string rowStr;
	SDL_Surface *fontSurf;
	for (int y = 0; y < rows; y++)
	{
		rowStr.clear();
		for (char &c : screen[y])
			rowStr.push_back(c);

		fontSurf = TTF_RenderText_Shaded(font, rowStr.c_str(), \
				{255, 255, 255}, {30, 30, 30});
		SDL_Rect offsetRect = { 0, fontSurf->h*y, fontSurf->w, fontSurf->h };
		screenTexture = SDL_CreateTextureFromSurface(renderer, fontSurf);
		SDL_RenderCopy(renderer, screenTexture, NULL, &offsetRect);
	}
	SDL_FreeSurface(fontSurf);
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
