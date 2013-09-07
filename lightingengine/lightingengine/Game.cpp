#include "Game.h"

#include "Image.h"

Game::Game() {
	
}

SDL_Texture *tex;

void Game::init() {
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);

	keepGoing = true;

	//Initialize things here
	tex = loadTexture(renderer, "pic.png");
}

void Game::deinit() {
	//Free things here (be clean!!)

	SDL_Quit();
}

void Game::start() {
	init();

	run();
}

void Game::stop() {
	deinit();
}

void Game::run() {
	SDL_Event event;

	while(keepGoing) {
		while(SDL_PollEvent(&event)) {
			onEvent(&event);
		}

		tick();
		draw();
	}
}

void Game::onEvent(SDL_Event *event) {
	switch(event->type) {
		case SDL_QUIT:
			keepGoing = false;
			break;
		case SDL_KEYDOWN:
			onKeydown(&event->key);
			break;
	}
}

void Game::onKeydown(SDL_KeyboardEvent *key) {
	
}

void Game::tick() {
	//Game logic goes here
}

void Game::draw() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Draw things here
	renderTexture(renderer, tex, 0, 0);

	SDL_RenderPresent(renderer);
}