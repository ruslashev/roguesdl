#include "serverstate.hpp"

ServerState ServerState::m_ServerState;

void ServerState::Enter()
{
	if (SDLNet_Init() < 0)
		fatal(1, "Failed to Initialize SDL_net: %s\n", SDLNet_GetError());

	if (SDLNet_ResolveHost(&IP, NULL, 1835) < 0)
		fatal(2, "Couldn't become a server (Listen on port): %s\n", SDLNet_GetError());

	if (!(sockDesc = SDLNet_TCP_Open(&IP)))
		fatal(2, "Failed to open TCP connetion: %s\n", SDLNet_GetError());

	term->clear();
	term->mvaddstr(0, 0, "Listening on port 1835");
	term->RebuildSurface();
}

void ServerState::Exit()
{
	SDLNet_TCP_Close(sockDesc);
	SDLNet_Quit();
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

	// Check if there is a pending connection
	if ((clSockDesc = SDLNet_TCP_Accept(sockDesc)))
	{
		// There is!
		// Now we can communicate with the client using clSockDesc socket
		// sockDesc will remain opened waiting other connections

		// Get the remote address
		remoteIP = SDLNet_TCP_GetPeerAddress(clSockDesc);
		if (!remoteIP)
			fatal(3, "Failed to get connected host's address: %s\n",
					SDLNet_GetError());
		printf("Host connected: ");
		clAddr = SDLNet_Read32(&remoteIP->host);
		printf("%d.%d.%d.%d:%d\n",
				(clAddr >> 24) & 0xFF, (clAddr >> 16) & 0xFF,
				(clAddr >> 8 ) & 0xFF, (clAddr >> 0 ) & 0xFF,
				SDLNet_Read16(&remoteIP->port));

		while (1)
		{
			if (SDLNet_TCP_Recv(clSockDesc, buffer, 512) > 0) {
				printf("<- %s\n", buffer);

				if (strcmp(buffer, "exit") == 0)
					break;
			}
		}

		SDLNet_TCP_Close(clSockDesc);
		gsm->done = true;
	}
}

