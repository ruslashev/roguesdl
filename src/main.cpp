#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "entity.hpp"
#include "gamestatemanager.hpp"
#include "main.hpp"
#include "terminal.hpp"
#include "world.hpp"
#include <fstream>
#include <vector>

Terminal term("Hai", 80, 25, "SourceCodePro-Regular.otf", 13);

class PlayState : public GameState
{
public:
	SDL_Keysym *key;
	Player dude;

	void Enter() {
		term.move(term.rows-4, 0);
		for (int i = 0; i < term.columns; i++) {
			term.move(term.rows-4, i);
			term.addch('-'); // ─
		}
		term.mvaddstr(term.rows-3, 1, "Dudebro");
		term.mvaddstr(term.rows-2, 1, "10/10");
		term.RebuildSurface();
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
	void Step() {
		key = term.getkey();

		SDL_WaitEvent(&term.event);
		gsm->done = (term.event.type == SDL_QUIT || \
				term.event.type == SDL_MOUSEBUTTONDOWN || \
				key->sym == SDLK_q);

		printf("%s ", SDL_GetKeyName(key->sym));

		if (key->sym == SDLK_h || key->sym == SDLK_LEFT) {
			term.mvaddch(dude.y, dude.x, ' ');
			dude.x--;
		} else if (key->sym == SDLK_j || key->sym == SDLK_DOWN) {
			term.mvaddch(dude.y, dude.x, ' ');
			dude.y++;
		} else if (key->sym == SDLK_k || key->sym == SDLK_UP) {
			term.mvaddch(dude.y, dude.x, ' ');
			dude.y--;
		} else if (key->sym == SDLK_l || key->sym == SDLK_RIGHT) {
			term.mvaddch(dude.y, dude.x, ' ');
			dude.x++;
		}

		term.mvaddch(dude.y, dude.x, dude.icon);
		term.RebuildSurface();
	}

	static PlayState* Instance() { return &m_PlayState; }
protected:
	PlayState() {}
private:
	static PlayState m_PlayState;
};

class IntroState : public GameState
{
public:
	void Enter() {
		term.mvaddstr(0, 0, "Entered IntroState!");
		term.RebuildSurface();
	}
	void Exit() {
		printf("IntroState::Exit\n");
	}
	void Pause() {
		printf("IntroState::Pause\n");
	}
	void Resume() {
		printf("IntroState::Resume\n");
	}
	void Step() {
		term.mvaddstr(1, 0, "Press enter to begin your ADVENTURE!");
		term.RebuildSurface();
		if (term.getkey()->sym == SDLK_RETURN)
			gsm->Push(PlayState::Instance());
	}

	static IntroState* Instance() { return &m_IntroState; }
protected:
	IntroState() {}
private:
	static IntroState m_IntroState;
};

int main()
{
	GameStateManager gsm;

	gsm.Push(IntroState::Instance());

	while (!gsm.done)
	{
		gsm.states.back()->Step();
		term.Draw();
	}

	return 0;
}

