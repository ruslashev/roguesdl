#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "entity.hpp"
#include "gamestatemanager.hpp"
#include "main.hpp"
#include "terminal.hpp"
#include "world.hpp"
#include <fstream>
#include <vector>

class PlayState : public GameState
{
public:
	Player dude;
	bool update;

	void Enter() {
		update = true;

		term->move(term->rows-4, 0);
		for (int i = 0; i < term->columns; i++) {
			term->move(term->rows-4, i);
			term->addch("—");
		}
		term->mvaddstr(term->rows-3, 1, "Dudebro");
		term->mvaddstr(term->rows-2, 1, "10/10");
		term->mvaddstr(term->rows-3, 20, "Гав");
		term->RebuildSurface();
	}
	void Exit() {
		printf("PlayState::Exit\n");
	}
	void Pause() {
		printf("PlayState::Pause\n");
	}
	void Resume() {
		printf("PlayState::Resume\n");
	}
	void Step(GameStateManager *gsm) {
		SDL_WaitEvent(&term->event);
		if (term->event.type == SDL_KEYDOWN) {
			key = term->event.key.keysym;
			// printf("Keydown: %s\n", SDL_GetKeyName(key.sym));
			update = true;
		}

		gsm->done = (term->event.type == SDL_QUIT || \
				term->event.type == SDL_MOUSEBUTTONDOWN);

		if (update) {
			if (key.sym == SDLK_h || key.sym == SDLK_LEFT) {
				term->mvaddch(dude.y, dude.x, " ");
				dude.x--;
			} else if (key.sym == SDLK_j || key.sym == SDLK_DOWN) {
				term->mvaddch(dude.y, dude.x, " ");
				dude.y++;
			} else if (key.sym == SDLK_k || key.sym == SDLK_UP) {
				term->mvaddch(dude.y, dude.x, " ");
				dude.y--;
			} else if (key.sym == SDLK_l || key.sym == SDLK_RIGHT) {
				term->mvaddch(dude.y, dude.x, " ");
				dude.x++;
			}
			term->mvaddch(dude.y, dude.x, std::string(1, dude.icon));

			term->RebuildSurface();
			term->Draw();
		}

		update = false;
	}

	static PlayState* Instance() { return &m_PlayState; }
	protected: PlayState() {}
	private: static PlayState m_PlayState;
};

class IntroState : public GameState
{
public:
	void Enter() {
		term->mvaddstr(0, 0, "Welcome to ...!");
		term->RebuildSurface();
	}
	void Exit() {
		printf("IntroState::Exit\n");
	}
	void Pause() {
		printf("IntroState::Pause\n");
		term->clear();
	}
	void Resume() {
		printf("IntroState::Resume\n");
	}
	void Step(GameStateManager *gsm) {
		term->mvaddstr(1, 0, "Press enter to begin your adventure!");
		term->RebuildSurface();
		term->Draw();

		key = term->getkey();

		if (key.sym == SDLK_RETURN)
			gsm->PushState(PlayState::Instance());
	}

	static IntroState* Instance() { return &m_IntroState; }
	protected: IntroState() {}
	private: static IntroState m_IntroState;
};

PlayState PlayState::m_PlayState;
IntroState IntroState::m_IntroState;

int main()
{
	Terminal term("Roguesdl", 80, 25, "DroidSansMono.ttf", 13);
	GameStateManager gsm;

	IntroState::Instance()->term = &term;
	PlayState::Instance()->term = &term;

	gsm.PushState(IntroState::Instance());

	while (!gsm.done)
	{
		gsm.states.back()->Step(&gsm);
	}

	return 0;
}

