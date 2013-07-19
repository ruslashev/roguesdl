#include "clientstate.hpp"

ClientState ClientState::m_ClientState;

void ClientState::Enter()
{
	if (SDLNet_Init() < 0)
		fatal(1, "Failed to Initialize SDL_net: %s\n", SDLNet_GetError());

	if (SDLNet_ResolveHost(&IP, "127.0.0.1", 1835) < 0)
		fatal(2, "Couldn't become a server (Listen on port): %s\n", SDLNet_GetError());

	if (!(sockDesc = SDLNet_TCP_Open(&IP)))
		fatal(2, "Failed to open TCP connetion: %s\n", SDLNet_GetError());

	term->clear();
	term->mvaddstr(0, 0, "Say hi");
	term->RebuildSurface();
}

void ClientState::Exit()
{
	SDLNet_TCP_Close(sockDesc);
	SDLNet_Quit();
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

	printf("> ");
	scanf("%s", buffer);

	len = strlen(buffer) + 1;
	if (SDLNet_TCP_Send(sockDesc, (void*)buffer, len) < len)
		fatal(3, "Couldn't send a message: %s\n", SDLNet_GetError());

	if (strcmp(buffer, "disonnect") == 0) {
		printf("Disconnecting\n");
		gsm->done = true;
	}
	if (strcmp(buffer, "exit") == 0) {
		printf("Disconnecting\n");
		gsm->done = true;
	}

	if (key.sym == SDLK_q)
		gsm->done = true;
}


