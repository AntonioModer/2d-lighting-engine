#include "Game.h"

#include "Image.h"

Game::Game(int w, int h) {
	screenWidth = w;
	screenHeight = h;
	ticks = 0;
	keepGoing = false;
	baseWindowTitle = "Lighting Engine | ";
}

SDL_Texture *tex;

void Game::init() {
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow(baseWindowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);

	keepGoing = true;

	//Set up log file
	logFile.open("log.txt", std::fstream::out);

	//Initialize OpenGL

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

	//Timing Variables
	double msPerFrame = 1000.0 / 60.0;
	double unprocessed = 0.0;
	Uint32 lastTime = SDL_GetTicks();
	Uint32 lastFPSTime = SDL_GetTicks();
	int frames = 0;
	int ticks = 0;
	bool vSync = false;
	bool ticked = false;
	//

	while(keepGoing) {
		ticked = false;

		while(SDL_PollEvent(&event)) {
			onEvent(&event);
		}

		//Do timing (keep us running at 60 ticks per second)
		Uint32 now = SDL_GetTicks();
		unprocessed += (now - lastTime) / msPerFrame;
		lastTime = now;

		while(unprocessed > 1) {
			tick();
			unprocessed--;
			ticked = true;
			ticks++;
		}
		if((ticked && vSync) || !vSync) {
			draw();
			frames++;
		}

		if(now > lastFPSTime + 1000) {
			//Put the FPS and ticks in the window title
			std::stringstream ss;
			ss << baseWindowTitle << "FPS: "<< frames << " Ticks: " << ticks;
			SDL_SetWindowTitle(window, ss.str().c_str());
			lastFPSTime += 1000;
			frames = 0;
			ticks = 0;
		}

		//Lets let the computer rest
		SDL_Delay(1);
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

	ticks++;
}

void Game::draw() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Draw things here
	renderTexture(renderer, tex, 0, 0);

	SDL_RenderPresent(renderer);
}
	
void Game::log(std::string s) {
	logFile << s;
}
void Game::log(std::string s, int i) {
	logFile << s << i;
}
void Game::log(std::string s, double d) {
	logFile << s << d;
}
void Game::logln(std::string s) {
	log(s);
	log("\n");
}
void Game::logln(std::string s, int i) {
	log(s, i);
	log("\n");
}
void Game::logln(std::string s, double d) {
	log(s, d);
	log("\n");
}