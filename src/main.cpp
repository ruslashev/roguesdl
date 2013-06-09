#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "entity.hpp"
#include "main.hpp"
#include "terminal.hpp"
#include <fstream>

int main()
{
	Terminal term("Hai", 80, 25, "SourceCodePro-Regular.otf", 13);
	Player dude;

	term.move(term.rows-4, 0);
	for (int i = 0; i < term.columns; i++) {
		term.move(term.rows-4, i);
		term.addch('-'); // ─
	}
	term.mvaddstr(term.rows-3, 1, "Dudebro");
	term.mvaddstr(term.rows-2, 1, "10/10");

	term.RebuildSurface();

	SDL_Keysym *key;

	bool done = false;
	while (!done)
	{
		SDL_WaitEvent(&term.event);
		done = (term.event.type == SDL_QUIT || \
				term.event.type == SDL_MOUSEBUTTONDOWN);

		key = term.getkey();

		if (key->sym == SDLK_h) {
			dude.x--;
			printf("h");
		} else if (key->sym == SDLK_j) {
			dude.y++;
			printf("j");
		} else if (key->sym == SDLK_k) {
			dude.y--;
			printf("k");
		} else if (key->sym == SDLK_l) {
			dude.x++;
			printf("l");
		}
		term.mvaddch(dude.y, dude.x, dude.icon);
		term.RebuildSurface();

		term.Draw();

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

