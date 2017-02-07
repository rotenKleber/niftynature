#include "game.hpp"

Game::Game() 
{
	for(int xx = 0; xx < MAP_W; xx++)
	{
		for(int yy = 0; yy < MAP_H; yy++)
		{
			map[xx][yy] = grass;
		}
	}
}

void Game::takeTurn() 
{
	for(auto it = organisms.begin(); it != organisms.end(); it++)
	{
		int dX = irandom(-1, 1);
		int dY = irandom(-1, 1);
		
		(*it)->move(dX, dY);
	}
}

Game::~Game()
{
	for(auto it = organisms.begin(); it != organisms.end(); it++)
	{
		delete *it;
	}
};
