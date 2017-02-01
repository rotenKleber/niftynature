#include "game.hpp"

Game::Game() {
	for(int xx = 0; xx < width; xx++) {
		for(int yy = 0; yy < height; yy++) {
			map[xx][yy][0] = dirt;
			map[xx][yy][1] = grass;
		}
	}
}

void Game::takeTurn() {
	// Loops through every organism and updates them
	for(auto it = organisms.begin(); it != organisms.end(); it++) {
		delete *it;
	}
}

Game::~Game() {
	for(auto it = organisms.begin(); it != organisms.end(); it++) {
		delete *it;
	}
};
