#include <stdio.h>
#include <stdlib.h>
#include "organism.hpp"
#include "ordertarget.hpp"
#include "consts.hpp"
#include "game.hpp"
#include "graphics.hpp"
#include <iostream>

int main()
{
	Game game;
	Graphics graphics(SCREEN_W, SCREEN_H);
	
	int code[nTraits] = {1, 1, 1};
	Organism* org = new Organism(code);
	org->setPosition(irandom(0, 10), irandom(0, 10));
	game.organisms.push_back(org);
	
	Organism* org2 = new Organism(code);
	org->setPosition(irandom(0, 10), irandom(0, 10));
	game.organisms.push_back(org2);

	Organism* org3 = new Organism(code);
	org3->setPosition(irandom(0, 10), irandom(0, 10));
	
	Organism** porg = &org;
	
	org3->orders.push_back(reinterpret_cast<Order*> (new OrderTarget(porg, fight)));
	game.organisms.push_back(org3);
	
	std::cout << "1" << std::endl;
	
	int framesUntilTurn = 5;
	int turns = 0;
	
	while(graphics.update(game.map, game.organisms))
	{
		framesUntilTurn--;
		if(framesUntilTurn == 0)
		{
			framesUntilTurn = 5;
			
			game.takeTurn();
			
			turns++;
		}
	}
	
	return 0;
}
