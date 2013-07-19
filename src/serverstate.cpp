#include "serverstate.hpp"

ServerState ServerState::m_ServerState;

void ServerState::Enter()
{
	term->clear();
	term->mvaddstr(0, 0, "Listening on port 1835");
	term->RebuildSurface();
}

void ServerState::Exit()
{
}

void ServerState::Pause()
{
}

void ServerState::Resume()
{
}

void ServerState::Step(GameStateManager *gsm)
{
	term->Draw();

	key = term->getkey();

	if (key.sym == SDLK_q)
		gsm->done = true;
}

