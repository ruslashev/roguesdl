#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "entity.hpp"
#include "gamestatemanager.hpp"
#include "introstate.hpp"
#include "main.hpp"
#include "playstate.hpp"
#include "terminal.hpp"
#include "world.hpp"
#include <fstream>
#include <vector>

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

