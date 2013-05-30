#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
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
	if (TTF_Init() == -1) {
		fprintf(stderr, "Failed to Initialize SDL_ttf: \"%s\"\n", TTF_GetError());
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
		return 2;
	}

	SDL_Texture *background = LoadImage("background.png", &renderer);

	int backgroundImgWidth, backgroundImgHeight;
	SDL_QueryTexture(background, NULL, NULL, &backgroundImgWidth, \
											&backgroundImgHeight);

	TTF_Font *font = TTF_OpenFont("SourceCodePro-Regular.otf", 13);
	if (font == NULL) {
		fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
		return 3;
	}
	TTF_SetFontHinting(font, TTF_HINTING_LIGHT);
	SDL_Surface *fontSurf = TTF_RenderText_Shaded(font, "beep boop woof", {255, 255, 255}, {0, 0, 0});
	SDL_Texture *fontText = SDL_CreateTextureFromSurface(renderer, fontSurf);
	SDL_FreeSurface(fontSurf);
	TTF_CloseFont(font);

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
		// SDL_RenderClear(renderer);

		ApplySurface(100, 200, fontText, renderer);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(background);
	SDL_DestroyTexture(fontText);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

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
