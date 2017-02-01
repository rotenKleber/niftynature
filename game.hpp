#ifndef GAME_H_
#define GAME_H_

#include "consts.hpp"
#include "organism.hpp"
#include <list>

class Game {
public:
	Game();
	~Game();
	
	void takeTurn();
	
	terrain map [20][20][3];
	list<Organism*> organisms;	
	int width, height;
};

#endif
