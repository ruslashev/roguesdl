#include "terminal.hpp"
#include "utils.hpp"

static SDL_Keysym dummyKey { SDL_SCANCODE_UNKNOWN, 0, 0, 0 };

Terminal::Terminal(const char* title, int cols, int rws, \
		const char* fontPath, int fontSize)
{
	columns = cols;
	rows = rws;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
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
	if (!window)
		fatal(2, "Failed to open a window: %s\n", SDL_GetError());

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | \
			SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
		fatal(2, "Failed to initialize a renderer: %s\n", SDL_GetError());

	TTF_SetFontHinting(font, TTF_HINTING_LIGHT);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

	screen.resize(rows);
	for (int y = 0; y < rows; y++)
		screen[y].resize(columns);

	clear();

	RebuildSurface();
}

void Terminal::RebuildSurface()
{
	std::string rowStr;
	SDL_Surface *fontSurf;
	SDL_Texture *screenTexture;
	for (int y = 0; y < rows; y++)
	{
		rowStr.clear();
		for (char &c : screen[y])
			rowStr.push_back(c);

		fontSurf = TTF_RenderText_Shaded(font, rowStr.c_str(), \
				{255, 255, 255, 255}, {20, 20, 20, 255});
		SDL_Rect offsetRect = { 0, fontSurf->h*y, fontSurf->w, fontSurf->h };
		screenTexture = SDL_CreateTextureFromSurface(renderer, fontSurf);
		SDL_RenderCopy(renderer, screenTexture, NULL, &offsetRect);
		SDL_FreeSurface(fontSurf);
		SDL_DestroyTexture(screenTexture);
	}
}

void Terminal::Draw()
{
	// SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Terminal::move(int y, int x)
{
	cursY = y;
	cursX = x;
}
void Terminal::addch(char c)
{
	if (cursX <= columns-1 && cursY <= rows-1)
		screen[cursY][cursX] = c;
}
void Terminal::addstr(std::string str)
{
	for (int x = cursX; x < cursX+(int)str.length(); x++)
	{
		if (x >= columns)
			break;
		screen[cursY][x] = str[x-cursX];
	}
}
void Terminal::mvaddch(int y, int x, char c)
{
	move(y, x);
	addch(c);
}
void Terminal::mvaddstr(int y, int x, std::string str)
{
	move(y, x);
	addstr(str);
}

void Terminal::clear()
{
	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
			screen[y][x] = ' ';
}

std::string Terminal::getch()
{
	std::string outStr = "?";
	SDL_StartTextInput();
	while (event.type != SDL_TEXTINPUT) {
		SDL_WaitEvent(&event);
		if (event.type == SDL_TEXTINPUT) {
			outStr = event.text.text;
			break;
		}
	}
	return outStr;
}
SDL_Keysym* Terminal::getkey()
{
	SDL_Keysym *key = &dummyKey;
	while (event.type != SDL_KEYDOWN) {
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN) {
			key = &event.key.keysym;
			break;
		}
	}
	return key;
}
// screw that
// std::string Terminal::getkeyv()
// {
// 	SDL_Keysym key = dummyKey;
// 	char textInputChar[100] = "unknown";
// 	std::string outStr;
//
// 	SDL_StartTextInput();
// 	while (SDL_PollEvent(&event)) {
// 		if (event.type == SDL_TEXTINPUT) {
// 			strcpy(textInputChar, event.text.text);
// 			// printf("SDL_TEXTINPUT: %s\n", event.text.text);
// 			break;
// 		}
// 	}
//
// 	printf("SDL_KEYDOWN: %s\n", SDL_GetKeyName(event.key.keysym.sym));
//
// 	// if (!strcmp(textInputChar, "unknown"))
// 	// 	outStr = SDL_GetKeyName(key.sym);
// 	// else
// 	// 	outStr = textInputChar;
//
// 	printf("textInputChar = %s, keyname = %s\n\n", textInputChar, \
// 			SDL_GetKeyName(key.sym));
// 	return "hai";
// }

Terminal::~Terminal()
{
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();

	SDL_Quit();
}
