#include "clientstate.hpp"

ClientState ClientState::m_ClientState;

void ClientState::Enter()
{
	term->clear();
	term->mvaddstr(0, 0, "Say hi");
	term->RebuildSurface();
}

void ClientState::Exit()
{
}

void ClientState::Pause()
{
}

void ClientState::Resume()
{
}

void ClientState::Step(GameStateManager *gsm)
{
	term->Draw();

	key = term->getkey();

	if (key.sym == SDLK_q)
		gsm->done = true;
}


