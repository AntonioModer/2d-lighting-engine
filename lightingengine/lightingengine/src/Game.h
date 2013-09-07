#pragma once


#ifdef _WIN32
#include <Windows.h>
#endif
#include <iostream>
#include <fstream>
#include <sstream>

#include "GL/gl.h"
#include "GL/glu.h"
#define NO_SDL_GLEXT
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_opengl.h"

class Game {
public:
	Game(int, int);

	void init();
	void deinit();

	void start();
	void stop();

	void run();

	void onEvent(SDL_Event*);
	void onKeydown(SDL_KeyboardEvent*);

	void tick();
	void draw();
	
	void log(std::string);
	void log(std::string, int);
	void log(std::string, double);
	void logln(std::string);
	void logln(std::string, int);
	void logln(std::string, double);

private:
	SDL_Window *window;
	SDL_Renderer *renderer;

	std::fstream logFile;

	int screenWidth, screenHeight;
	long ticks;
	bool keepGoing;

	std::string baseWindowTitle;
};