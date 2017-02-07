#ifndef GAME_H_
#define GAME_H_

#include "consts.hpp"
#include "organism.hpp"
#include <list>

class Game
{
public:
	Game();
	~Game();
	
	void takeTurn();
	
	terrain map [MAP_W][MAP_H];
	list<Organism*> organisms;		
};

#endif
