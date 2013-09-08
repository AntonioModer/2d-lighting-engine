#pragma once

/* Resources:

https://www.youtube.com/watch?v=LL9BrNrO11o
http://www.gamedev.net/page/resources/_/technical/graphics-programming-and-theory/dynamic-2d-soft-shadows-r2032

*/

#ifdef _WIN32
#include <Windows.h>
#endif
#include <iostream>
#include <fstream>
#include <sstream>

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#define NO_SDL_GLEXT
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#include "Scene.h"
#include "Polygon.h"

extern std::fstream logFile;

class Game {
public:
	Game(int, int);

	void init();
	void deinit();

	void resizeWindow(int, int);

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

	SDL_GLContext glcontext;

	int screenWidth, screenHeight;
	long ticks;
	bool keepGoing;

	std::string baseWindowTitle;
};