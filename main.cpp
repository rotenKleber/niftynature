#include <stdio.h>
#include <stdlib.h>
#include "organism.hpp"
#include "consts.hpp"
#include "game.hpp"
#include "graphics.hpp"

int main()
{
	Game game;
	Graphics graphics(640, 480);

	srand(time(NULL));
	
	int code[nTraits] = {1, 1, 1};
	Organism* org = new Organism(code);
	
	org->setPosition(5, 5);

	game.organisms.push_back(org);
	
	for (int i = 0; i < 10; i++)
	{
		game.organisms.push_back(new Organism(code));
	}

	int framesUntilTurn = 30;
	
	while(graphics.update(game.map, game.organisms))
	{
		framesUntilTurn--;
		if(framesUntilTurn == 0)
		{
			framesUntilTurn = 30;
			
			game.takeTurn();
		}
	}
	
	return 0;
}
