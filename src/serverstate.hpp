#ifndef SERVERSTATE_HPP
#define SERVERSTATE_HPP
#include "SDL2/SDL_net.h"
#include "gamestatemanager.hpp"
#include "terminal.hpp"
#include "utils.hpp"

class ServerState : public GameState
{
public:
	TCPsocket sockDesc, clSockDesc;
	IPaddress IP, *remoteIP;
	char buffer[512];
	bool quit, quit2;

	void Enter();
	void Exit();
	void Pause();
	void Resume();
	void Step(GameStateManager *gsm);

	static ServerState* Instance() { return &m_ServerState; }
	protected: ServerState() {}
	private: static ServerState m_ServerState;
};

#endif

