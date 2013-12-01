#include "introstate.hpp"

IntroState IntroState::m_IntroState;

void IntroState::Enter()
{
	term->mvaddstr(3, term->columns/2-14/2, "Welcome to ...");

	const char *splash[5] = {
		R"(   ___                     ___ _      ______________  __  _______)",
		R"(  / _ \___  ___ ___ _____ / _ | | /| / / __/ __/ __ \/  |/  / __/)",
		R"( / , _/ _ \/ _ `/ // / -_) __ | |/ |/ / _/_\ \/ /_/ / /|_/ / _/)",
		R"(/_/|_|\___/\_, /\_,_/\__/_/ |_|__/|__/___/___/\____/_/  /_/___/)",
		R"(          /___/)"
	};

	term->mvaddstr(6,  7, splash[0]);
	term->mvaddstr(7,  7, splash[1]);
	term->mvaddstr(8,  7, splash[2]);
	term->mvaddstr(9,  7, splash[3]);
	term->mvaddstr(10, 7, splash[4]);

	term->mvaddstr(14, term->columns/2-36/2, "Press enter to begin your adventure!");

	term->RebuildSurface();
}

void IntroState::Exit()
{
	printf("IntroState::Exit\n");
}

void IntroState::Pause()
{
	printf("IntroState::Pause\n");
	term->clear();
}

void IntroState::Resume()
{
	printf("IntroState::Resume\n");
}

void IntroState::Step(GameStateManager *gsm)
{
	term->Draw();

	key = term->getkey();

	term->mvaddstr(17, term->columns/2-22/2, "Who do you want to be?");
	term->mvaddstr(18, term->columns/2-10/2, "(A) Server");
	term->mvaddstr(19, term->columns/2-10/2, "(B) Client");
	term->RebuildSurface();

	if (key.sym == SDLK_a)
		gsm->PushState(ServerState::Instance());
	if (key.sym == SDLK_b)
		gsm->PushState(ClientState::Instance());

	if (key.sym == SDLK_q)
		gsm->done = true;
}

