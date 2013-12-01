#include "playstate.hpp"

PlayState PlayState::m_PlayState;

void PlayState::Enter()
{
	update = true;

	term->move(term->rows-4, 0);
	for (int i = 0; i < term->columns; i++) {
		term->move(term->rows-4, i);
		term->addch("—");
	}
	term->mvaddstr(term->rows-3, 1, "Dudebro");
	term->mvaddstr(term->rows-2, 1, "10/10");
	term->RebuildSurface();
}

void PlayState::Exit()
{
	printf("PlayState::Exit\n");
}

void PlayState::Pause()
{
	printf("PlayState::Pause\n");
}

void PlayState::Resume()
{
	printf("PlayState::Resume\n");
}

void PlayState::Step(GameStateManager *gsm)
{
	SDL_WaitEvent(&term->event);
	if (term->event.type == SDL_KEYDOWN) {
		key = term->event.key.keysym;
		// printf("Keydown: %s\n", SDL_GetKeyName(key.sym));
		update = true;
	}

	gsm->done = (term->event.type == SDL_QUIT ||
			term->event.type == SDL_MOUSEBUTTONDOWN || key.sym == SDLK_q);

	if (update) {
		if (key.sym == SDLK_h || key.sym == SDLK_LEFT) {
			if (dude.x > 0) {
				term->mvaddch(dude.y, dude.x, " ");
				dude.x--;
			}
		} else if (key.sym == SDLK_j || key.sym == SDLK_DOWN) {
			if (dude.y < world.height-1) {
				term->mvaddch(dude.y, dude.x, " ");
				dude.y++;
			}
		} else if (key.sym == SDLK_k || key.sym == SDLK_UP) {
			if (dude.y > 0) {
				term->mvaddch(dude.y, dude.x, " ");
				dude.y--;
			}
		} else if (key.sym == SDLK_l || key.sym == SDLK_RIGHT) {
			if (dude.x < world.width-1) {
				term->mvaddch(dude.y, dude.x, " ");
				dude.x++;
			}
		}

		for (int y = 0; y < world.height; y++) {
			for (int x = 0; x < world.width; x++) {
				term->mvaddch(y, x, std::string(1, world.map[y][x]));
			}
		}

		term->mvaddch(dude.y, dude.x, std::string(1, dude.icon));

		term->RebuildSurface();
		term->Draw();
	}

	update = false;
}

