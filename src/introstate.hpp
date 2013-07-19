#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP
#include "entity.hpp"
#include "gamestatemanager.hpp"
#include "playstate.hpp"
#include "terminal.hpp"
#include "world.hpp"
#include "serverstate.hpp"
#include "clientstate.hpp"

class IntroState : public GameState
{
public:
	void Enter();
	void Exit();
	void Pause();
	void Resume();
	void Step(GameStateManager *gsm);

	static IntroState* Instance() { return &m_IntroState; }
	protected: IntroState() {}
	private: static IntroState m_IntroState;
};

#endif

