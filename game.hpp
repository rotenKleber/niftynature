#ifndef GAME_H_
#define GAME_H_

#include "consts.hpp"
#include "organism.hpp"
#include <list>
#include "direction.hpp"
#include "movement.hpp"

class Game
{
public:
	Game();
	~Game();
	
	void takeTurn();
	bool move(list<Organism*>::iterator it);
	
	bool isFree(int x, int y);
	
	terrain map [MAP_W][MAP_H][2];
	list<Organism*> organisms;		
};

#endif
