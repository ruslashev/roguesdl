#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "main.hpp"
#include "terminal.hpp"
#include <fstream>

int main()
{
	Terminal term("Hai", 80, 30, "SourceCodePro-Regular.otf", 13);

	bool done = false;
	while (!done)
	{
		while (SDL_PollEvent(&term.events)) {
			switch (term.events.type)
			{
				case SDL_QUIT:
				case SDL_KEYDOWN:
				case SDL_MOUSEBUTTONDOWN:
					done = true;
					break;
			}
		}
		// SDL_RenderClear(renderer);

		ApplySurface(100, 200, term.fontText, term.renderer);

		SDL_RenderPresent(term.renderer);
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

void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend)
{
	SDL_Rect pos = { x, y };

	SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
	SDL_RenderCopy(rend, tex, NULL, &pos);
}
