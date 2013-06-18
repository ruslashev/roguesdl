#ifndef GAMESTATEMANAGER_HPP
#define GAMESTATEMANAGER_HPP

#include "utils.hpp"
#include <vector>

class GameState
{
public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void Step() = 0; // aka Update
};

class GameStateManager
{
public:
	std::vector<GameState*> states;
	bool done;

	void ChangeTo(GameState *newState) {
		if (!states.empty()) {
			states.back()->Exit();
			states.pop_back();
		}
		states.push_back(newState);
		states.back()->Enter();
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
		if (!states.empty()) {
			states.back()->Resume();
		} else {
			fatal(1, "Tried to pop state from stack with only one state!\n");
		}
	}
};

#endif
