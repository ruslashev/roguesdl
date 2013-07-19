#ifndef CLIENTSTATE_HPP
#define CLIENTSTATE_HPP
#include "SDL2/SDL_net.h"
#include "gamestatemanager.hpp"
#include "terminal.hpp"

class ClientState : public GameState
{
public:
	TCPsocket sockDesc, clSockDesc;
	IPaddress IP, *remoteIP;
	char buffer[512];
	int len;

	void Enter();
	void Exit();
	void Pause();
	void Resume();
	void Step(GameStateManager *gsm);

	static ClientState* Instance() { return &m_ClientState; }
	protected: ClientState() {}
	private: static ClientState m_ClientState;
};

#endif


