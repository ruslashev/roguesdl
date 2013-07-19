#ifndef CLIENTSTATE_HPP
#define CLIENTSTATE_HPP
#include "gamestatemanager.hpp"
#include "terminal.hpp"

class ClientState : public GameState
{
public:
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


