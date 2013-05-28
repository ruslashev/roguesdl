#include <fstream>
#include "SDL2/SDL.h"

int main()
{
	printf("Sup world\n");

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		printf("SDL errored with message: \"%s\"", SDL_GetError());
		return 1;
	}

	SDL_Window *win = nullptr;
	win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, \
											SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		printf("Couldn't open a window: %s", SDL_GetError());
		return 1;
	}

	SDL_Renderer *ren = nullptr;
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | \
										SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		printf("Couldn't initialize a renderer: %s", SDL_GetError());
		return 1;
	}

	SDL_Surface *bmp = nullptr;
	bmp = SDL_LoadBMP("sprite.bmp");
	if (bmp == nullptr){
		printf("Bad image: %s", SDL_GetError());
		return 1;
	}

	SDL_Texture *tex = nullptr;
	tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);

	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, tex, NULL, NULL);
	SDL_RenderPresent(ren);

	SDL_Delay(5000);

	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	SDL_Quit();

	return 0;
}
