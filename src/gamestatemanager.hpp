#ifndef GAMESTATEMANAGER_HPP
#define GAMESTATEMANAGER_HPP

#include "utils.hpp"
#include "terminal.hpp"
#include <vector>

class GameStateManager;

class GameState
{
public:
	// Terminal *term;
	GameStateManager *gsm;

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void Step() = 0; // aka Update

protected:
	GameState() {}
};

class GameStateManager
{
public:
	std::vector<GameState*> states;
	bool done;

	void ChangeTo(GameState *newState) {
		Pop();
		Push(newState);
	}

	void Push(GameState *newState) {
		if (!states.empty())
			states.back()->Pause();

		states.push_back(newState);
		states.back()->Enter();
	}

	void Pop() {
		if (!states.empty()) {
			states.back()->Exit();
			states.pop_back();
		} else {
			warning("Tried to pop from an empty state stack!\n");
		}
		if (!states.empty())
			states.back()->Resume();
	}
};

#endif
