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

	quit = quit2 = false;
	while (!quit)
	{
		if (key.sym == SDLK_q)
			gsm->done = true;

		// Check if there is a pending connection
		if ((clSockDesc = SDLNet_TCP_Accept(sockDesc)))
		{
			// Now we can communicate with the client using clSockDesc socket
			// sockDesc will remain opened waiting other connections
 
			// Get the remote address
			if ((remoteIP = SDLNet_TCP_GetPeerAddress(clSockDesc)))
				printf("Host connected: %x:%d\n", SDLNet_Read32(&remoteIP->host), SDLNet_Read16(&remoteIP->port));
			else
				fatal(3, "Failed to get connected host's address: %s\n", SDLNet_GetError());
 
			while (!quit2)
			{
				if (SDLNet_TCP_Recv(clSockDesc, buffer, 512) > 0)
				{
					printf("<client> %s\n", buffer);
 
					if (strcmp(buffer, "disconnect") == 0)
						quit2 = true;
					if (strcmp(buffer, "exit") == 0)
						quit2 = quit = true;
				}
			}
 
			// Close the client socket
			SDLNet_TCP_Close(clSockDesc);
		}
	}

	if (key.sym == SDLK_q)
		gsm->done = true;
}

