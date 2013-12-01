#ifndef GAMESTATEMANAGER_HPP
#define GAMESTATEMANAGER_HPP

#include "utils.hpp"
#include "terminal.hpp"

#include <vector>

class GameState;

class GameStateManager
{
public:
	bool done;
	std::vector<GameState*> states;

	void ChangeTo(GameState *newState);
	void PushState(GameState *newState);
	void PopState();

	GameStateManager() : done(false) {}
};

class GameState
{
public:
	Terminal *term;
	SDL_Keysym key;

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void Step(GameStateManager *gsm) = 0; // aka Update

protected:
	GameState() {}
};

#endif
