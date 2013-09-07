#include "src/Game.h"
 
int main(int argc, char** argv){
	Game *game = new Game(800, 600);
	game->start();
 
    return 0;
}