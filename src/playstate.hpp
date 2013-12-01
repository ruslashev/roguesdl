#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "entity.hpp"
#include "gamestatemanager.hpp"
#include "introstate.hpp"
#include "terminal.hpp"
#include "world.hpp"

class PlayState : public GameState
{
public:
	Player dude;
	World world;
	bool update;

	void Enter();
	void Exit();
	void Pause();
	void Resume();
	void Step(GameStateManager *gsm);

	static PlayState* Instance() { return &m_PlayState; }
	protected: PlayState() : world(10, 20) {}
	private: static PlayState m_PlayState;
};

#endif

