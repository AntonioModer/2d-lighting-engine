#pragma once

#include "SDL.h"

class Game {
public:
	Game();

	void init();
	void deinit();

	void start();
	void stop();

	void run();

	void onEvent(SDL_Event*);
	void onKeydown(SDL_KeyboardEvent*);

	void tick();
	void draw();

private:
	SDL_Window *window;
	SDL_Renderer *renderer;

	bool keepGoing;
};