#ifndef SERVERSTATE_HPP
#define SERVERSTATE_HPP
#include "gamestatemanager.hpp"
#include "terminal.hpp"

class ServerState : public GameState
{
public:
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

