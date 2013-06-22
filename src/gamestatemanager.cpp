#include "gamestatemanager.hpp"

void GameStateManager::ChangeTo(GameState *newState) {
	PopState();
	PushState(newState);
}

void GameStateManager::PushState(GameState *newState) {
	if (!states.empty())
		states.back()->Pause();

	states.push_back(newState);
	states.back()->Enter();
}

void GameStateManager::PopState() {
	if (!states.empty()) {
		states.back()->Exit();
		states.pop_back();
	} else {
		warning("Tried to pop from an empty state stack!\n");
	}
	if (!states.empty())
		states.back()->Resume();
}

