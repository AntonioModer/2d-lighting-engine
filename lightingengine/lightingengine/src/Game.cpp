#include "Game.h"

#include "Image.h"

long nanoSeconds() {
#ifdef _WIN32
	SYSTEMTIME time;
	GetSystemTime(&time);
	return (time.wSecond * 1000) + time.wMilliseconds;
#else
	timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
#endif
}

Game::Game(int w, int h) {
	screenWidth = w;
	screenHeight = h;
	ticks = 0;
	keepGoing = false;
}

SDL_Texture *tex;

void Game::init() {
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);

	keepGoing = true;

	//Set up log file
	logFile.open("log.txt", std::fstream::out);

	//Initialize things here
	tex = loadTexture(renderer, "pic.png");
}

void Game::deinit() {
	//Free things here (be clean!!)

	logFile.close();

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