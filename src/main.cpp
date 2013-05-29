#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "main.hpp"
#include <fstream>

int main()
{
	SDL_Renderer *renderer = NULL;
	SDL_Event ev;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		fprintf(stderr, "SDL errored with message: \"%s\"\n", SDL_GetError());
		return 1;
	}
	SDL_Window *window = SDL_CreateWindow("Hello World!\n", \
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,\
			SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "Couldn't open a window: %s\n", SDL_GetError());
		return 2;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | \
			SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		fprintf(stderr, "Couldn't initialize a renderer: %s\n", SDL_GetError());
		return 3;
	}

	SDL_Texture *background = LoadImage("background.png", &renderer);

	int backgroundImgWidth, backgroundImgHeight;
	SDL_QueryTexture(background, NULL, NULL, &backgroundImgWidth, \
											&backgroundImgHeight);

	double x = 0, y = 0;
	bool done = false;
	while (!done)
	{
		while (SDL_PollEvent(&ev)) {
			switch (ev.type)
			{
				case SDL_QUIT:
				case SDL_KEYDOWN:
				case SDL_MOUSEBUTTONDOWN:
					done = true;
					break;
			}
		}
		SDL_RenderClear(renderer);

		x = x+0.01;
		y = y+0.01;
		ApplySurface(x*backgroundImgWidth, y*backgroundImgHeight, \
						background, renderer);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}

SDL_Texture* LoadImage(const char* imagePath, SDL_Renderer **rend)
{
	SDL_Texture* tex = IMG_LoadTexture(*rend, imagePath);
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
