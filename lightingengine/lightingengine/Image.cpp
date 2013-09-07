#include "Image.h"

SDL_Texture *loadTexture(SDL_Renderer *renderer, std::string filename) {
	SDL_Surface *loadedSurface = NULL;
	SDL_Texture *texture = NULL;

	loadedSurface = IMG_Load(filename.c_str());

	if(loadedSurface == NULL) {
		//There has been an issue
		std::cout << "Error loading image " << filename << " " << SDL_GetError() << std::endl;
	}
	else {
		//Continue normally if everything's cool
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		SDL_FreeSurface(loadedSurface);
	}

	return texture;
}

void renderTexture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}