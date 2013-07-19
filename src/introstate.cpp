#include "introstate.hpp"

IntroState IntroState::m_IntroState;

void IntroState::Enter() {
	term->mvaddstr(3, term->columns/2-14/2, "Welcome to ...");

	term->mvaddstr(6, 6, \
		"   ___                     ___ _      ______________  __  _______");
	term->mvaddstr(7, 6, \
		"  / _ \\___  ___ ___ _____ / _ | | /| / / __/ __/ __ \\/  |/  / __/");
	term->mvaddstr(8, 6, \
		" / , _/ _ \\/ _ `/ // / -_) __ | |/ |/ / _/_\\ \\/ /_/ / /|_/ / _/");
	term->mvaddstr(9, 6, \
		"/_/|_|\\___/\\_, /\\_,_/\\__/_/ |_|__/|__/___/___/\\____/_/  /_/___/");
	term->mvaddstr(10, 6, \
		"          /___/");

	term->mvaddstr(14, term->columns/2-36/2, "Press enter to begin your adventure!");

	term->RebuildSurface();
}

void IntroState::Exit() {
	printf("IntroState::Exit\n");
}

void IntroState::Pause() {
	printf("IntroState::Pause\n");
	term->clear();
}

void IntroState::Resume() {
	printf("IntroState::Resume\n");
}

void IntroState::Step(GameStateManager *gsm) {
	term->Draw();

	key = term->getkey();

	if (key.sym == SDLK_RETURN)
		gsm->PushState(PlayState::Instance());
	if (key.sym == SDLK_q)
		gsm->done = true;
}

