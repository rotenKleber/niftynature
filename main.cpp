#include <stdio.h>
#include <stdlib.h>
#include "organism.hpp"
#include "consts.hpp"
#include "game.hpp"
#include "graphics.hpp"

int main()
{
	Game game;
	Graphics graphics(SCREEN_W, SCREEN_H);
	
	int code[nTraits] = {1, 1, 1};
	
	for (int i = 0; i < 1; i++)
	{
		Organism* org = new Organism(code);
			
		org->setPosition(5, 5);
		
		org->setTarget(10, 10);
		org->setHasTarget(true);

		game.organisms.push_back(org);	
	}

	int framesUntilTurn = 5;
	
	while(graphics.update(game.map, game.organisms))
	{
		framesUntilTurn--;
		if(framesUntilTurn == 0)
		{
			framesUntilTurn = 5;
			
			game.takeTurn();
		}
	}
	
	return 0;
}
