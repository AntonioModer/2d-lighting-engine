#pragma once

/* Resources:

https://www.youtube.com/watch?v=LL9BrNrO11o
http://www.gamedev.net/page/resources/_/technical/graphics-programming-and-theory/dynamic-2d-soft-shadows-r3065

*/

#ifdef _WIN32
#include <Windows.h>
#endif
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#define NO_SDL_GLEXT
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include "Scene.h"

extern std::fstream logFile;
extern Uint32 lastMouseState;

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

	Scene *curScene;

	int screenWidth, screenHeight;
	long ticks;
	bool keepGoing;

	std::string baseWindowTitle;
};