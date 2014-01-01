#pragma once

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>

SDL_Texture *loadTexture(SDL_Renderer*, std::string);
void renderTexture(SDL_Renderer*, SDL_Texture*, int, int);