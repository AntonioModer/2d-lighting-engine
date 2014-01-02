#include "Game.h"

std::fstream logFile;
Uint32 lastMouseState;

Game::Game(int w, int h) {
	screenWidth = w;
	screenHeight = h;
	ticks = 0;
	keepGoing = false;
	baseWindowTitle = "Lighting Engine | ";
}

void Game::init() {
	//Set up log file
	logFile.open("log.txt", std::fstream::out);
	//Make std::cerr redirect to the log file
	std::cerr.rdbuf(logFile.rdbuf());

	logFile << "Initializing...\n";

	SDL_Init(SDL_INIT_EVERYTHING);

	if((window = SDL_CreateWindow(baseWindowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL)) == 0) {
		logFile << "Error creating window: " << SDL_GetError() << std::endl;
		stop();
		return;
	}
	logFile << "Created window" << std::endl;
	if((renderer = SDL_CreateRenderer(window, -1, 0)) == NULL) {
		logFile << "Error creating renderer: " << SDL_GetError() << std::endl;
		stop();
		return;
	}
	logFile << "Created renderer" << std::endl;
	if((glcontext = SDL_GL_CreateContext(window)) == NULL) {
		logFile << "Error creating OpenGL context: " << SDL_GetError() << std::endl;
		stop();
		return;
	}
	glewInit();
	logFile << "Created OpenGL context" << std::endl;

	//Initialize OpenGL
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	resizeWindow(screenWidth, screenHeight);

	lastMouseState = 0;

	//Initialize things here

	curScene = new Scene();

	//

	logFile << "Finished initializing" << std::endl;
}

void Game::deinit() {
	//Free things here (be clean!!)

	logFile << "Deinitializing" << std::endl;

	SDL_GL_DeleteContext(glcontext);

	SDL_DestroyWindow(window);

	SDL_Quit();

	logFile.close();
}

void Game::resizeWindow(int width, int height) {
	if(height == 0)
		height = 1;

	logFile << "Resizing window to " << width << "x" << height << "..." << std::endl;

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glViewport(0, 0, screenWidth, screenHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, screenWidth, screenHeight, 0.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	glDisable(GL_CULL_FACE);

	logFile << "Finished resizing" << std::endl;
}

void Game::start() {
	logFile << "Game starting" << std::endl;
	keepGoing = true;
	run();
}

void Game::stop() {
	keepGoing = false;
}

void Game::run() {
	init();

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
			ss << baseWindowTitle << "FPS: "<< frames << " Ticks: " << ticks << " # of Lights: " << curScene->lights.size();
			SDL_SetWindowTitle(window, ss.str().c_str());
			lastFPSTime += 1000;
			frames = 0;
			ticks = 0;
		}

		//Lets let the computer rest
		SDL_Delay(1);
	}

	deinit();
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
	switch(key->keysym.sym) {
	case SDLK_ESCAPE:
		stop();
		break;
	}
}

void Game::tick() {
	//Game logic goes here
	curScene->tick();
	//

	lastMouseState = SDL_GetMouseState(NULL, NULL);
	ticks++;
}

void Game::draw() {
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw things here
	curScene->draw();
	//

	SDL_GL_SwapWindow(window);
}