#ifndef GAME_H_
#define GAME_H_

#include "consts.hpp"
#include "organism.hpp"
#include <list>
#include <stdlib.h>
#include "direction.hpp"
#include "movement.hpp"
#include "order.hpp"
#include "ordertarget.hpp"
#include <iostream>

class Game
{
public:
	Game();
	~Game();
	
	void takeTurn();
	
	void performJob(Organism* it, job j);
	
	bool move(Organism* it);
	
	bool isFree(int x, int y);
	pair<int, int> getNearestTerrain(int x, int y, terrain t);
	Organism** getNearestHerbivore(int x, int y, terrain t);
	
	terrain map [MAP_W][MAP_H][2];
	list<Organism*> organisms;		
};

#endif
