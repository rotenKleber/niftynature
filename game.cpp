#include "game.hpp"

Game::Game(int w, int h):
	width(w),
	height(h)
{
	for(int xx = 0; xx < width; xx++) {
		for(int yy = 0; yy < height; yy++) {
			map[xx][yy][0] = dirt;
			map[xx][yy][1] = grass;
		}
	}
}

Game::~Game() {
	for(auto it = organisms.begin(); it != organisms.end(); it++) {
		delete *it;
	}
};
