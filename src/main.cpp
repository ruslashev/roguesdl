#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "entity.hpp"
#include "main.hpp"
#include "terminal.hpp"
#include "world.hpp"
#include <fstream>

enum GameStates {
	Splash = 1,
	Intro,
	Game
};

void UpdateState(GameStates *gameState, Terminal &term)
{
	switch (*gameState)
	{
	case Splash:
		term.mvaddstr(0, 0, "Splash!");
		term.RebuildSurface();
		break;
	case Intro:
		term.mvaddstr(0, 0, "Intro!");
		term.RebuildSurface();
		break;
	case Game:
		term.mvaddstr(0, 0, "Game!");
		term.RebuildSurface();
	}
}

int main()
{
	Terminal term("Hai", 80, 25, "SourceCodePro-Regular.otf", 13);

	Player dude;

	// term.move(term.rows-4, 0);
	// for (int i = 0; i < term.columns; i++) {
	// 	term.move(term.rows-4, i);
	// 	term.addch('-'); // ─
	// }
	// term.mvaddstr(term.rows-3, 1, "Dudebro");
	// term.mvaddstr(term.rows-2, 1, "10/10");
	// term.RebuildSurface();

	GameStates currentState = Splash;

	// SDL_Keysym *key;

	bool done = false;
	while (!done)
	{
		// key = term.getkey();

		// SDL_WaitEvent(&term.event);
		// done = (term.event.type == SDL_QUIT || \
		// 		term.event.type == SDL_MOUSEBUTTONDOWN || \
		// 		key->sym == SDLK_q);

		// printf("%s ", SDL_GetKeyName(key->sym));

		// if (key->sym == SDLK_h || key->sym == SDLK_LEFT) {
		// 	term.mvaddch(dude.y, dude.x, ' ');
		// 	dude.x--;
		// } else if (key->sym == SDLK_j || key->sym == SDLK_DOWN) {
		// 	term.mvaddch(dude.y, dude.x, ' ');
		// 	dude.y++;
		// } else if (key->sym == SDLK_k || key->sym == SDLK_UP) {
		// 	term.mvaddch(dude.y, dude.x, ' ');
		// 	dude.y--;
		// } else if (key->sym == SDLK_l || key->sym == SDLK_RIGHT) {
		// 	term.mvaddch(dude.y, dude.x, ' ');
		// 	dude.x++;
		// }

		// term.mvaddch(dude.y, dude.x, dude.icon);
		// term.RebuildSurface();

		UpdateState(&currentState, term);
		term.Draw();
	}

	return 0;
}

