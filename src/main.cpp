#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "main.hpp"
#include "terminal.hpp"
#include <fstream>

int main()
{
	Terminal term("Hai", 80, 25, "SourceCodePro-Regular.otf", 13);

	term.move(0, 0);
	term.addch('r');
	term.move(1, 0);
	term.addstr("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-");

	term.mvaddch(3, 2, 's');
	term.mvaddch(2, 2, '|');
	term.mvaddstr(3, 5, "peeeew pew pepwwp");

	term.RebuildSurface();

	// std::string in = " ";
	SDL_Keysym *key;

	Uint32 eventType;
	bool done = false;
	while (!done)
	{
		SDL_WaitEvent(&term.event);
		eventType = term.event.type;
		done = (eventType == SDL_QUIT || eventType == SDL_MOUSEBUTTONDOWN);
		printf("Update!\n");

		term.Draw();

		key = term.getkey();

		if (key->sym == SDLK_q)
			done = true;
	}

	return 0;
}

SDL_Texture* LoadImage(const char* imagePath, SDL_Renderer **rend)
{
	SDL_Texture* tex = IMG_LoadTexture(*rend, imagePath);
	// TODO
	if (tex == NULL)
		fprintf(stderr, "Failed to load image \"%s\": %s\n", imagePath, \
					IMG_GetError());

	return tex;
}

