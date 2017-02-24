#include "game.hpp"

Game::Game() 
{
	srand(time(NULL));
	
	for(int xx = 0; xx < MAP_W; xx++)
	{
		for(int yy = 0; yy < MAP_H; yy++)
		{
			if (irandom(0, 2) == 0)
			{
				map[xx][yy][1] = stone;
			}
		}
	}
}

bool Game::move(list<Organism*>::iterator it)
{
	Organism& o = *(*it);
	
	// Movement
	if(o.memory.empty())
	{
		// Creating "impulse"/first movements
		if(!o.hasTarget())
		{
			o.move(irandom(-1, 1), irandom(-1, 1));
		}
		else
		{
			int dX, dY;
			dX = o.getTargetX() - o.getX();
			dY = o.getTargetY() - o.getY();
			
			if(dX > dY)
			{
				if(dX > 0)
				{
					o.memory.push(Movement(RIGHT, RIGHT));
					move(it);
				}
				else if(dX < 0)
				{
					o.memory.push(Movement(LEFT, LEFT));
					move(it);
				}
			}
			else
			{
				if(dY > 0)
				{
					o.memory.push(Movement(DOWN, DOWN));
					move(it);
				}
				else if(dY < 0)
				{
					o.memory.push(Movement(UP, UP));
					move(it);
				}
			}
		}
	}
	else
	{
		int dec = Direction::dec(o.memory.top().attempted);
		
		cardinal attempted = o.memory.top().attempted;
		cardinal substituted = o.memory.top().substituted;
		
		bool canMove = false;

		if(attempted == LEFT || attempted == RIGHT)
		{
			if(isFree( o.getX() + dec, o.getY() ))
			{
				o.move(dec, 0);
				canMove = true;
			}
		}
		else
		{
			if(isFree( o.getX(), o.getY() + dec ))
			{
				o.move(0, dec);
				canMove = true;
			}
		}
		
		if(!canMove)
		{
			// If this has no movement in memory besides impulse move
			if(o.memory.size() == 1)
			{
				// Moves at random parallel movement
				o.memory.push(Movement(substituted, Direction::getParallel(substituted)));
				move(it);
			}
			else
			{
				o.memory.push(Movement(substituted, Direction::getOpposite(attempted)));
				move(it);
			}
		}
		else
		{
			o.memory.pop(); // remove last movement memory
		}
	}

	/*
	if((map [o.getX() + dX] [o.getY() + dY] [1] == grass) && o.isHungry())
	{
		o.eat(cellulose, 15);
		
		map [o.getX() + dX] [o.getY() + dY] [1] = none;
	}
	*/
	
	// Kill organisms that run out of energy
	if(o.getEnergy() <= 0)
	{
		return true;
	}
	
	return false;
}

void Game::takeTurn() 
{
	for(auto it = organisms.begin(); it != organisms.end(); it++)
	{
		if(move(it))
		{	
			printf("Ok\n");
			// Free organism
			delete *it;
			
			// Remove it from the list
			// And reset iterator
			it = organisms.erase(it);
		}
	}
}

bool Game::isFree(int x, int y)
{
	if(map[x][y][1] != stone)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Game::~Game()
{
	for(auto it = organisms.begin(); it != organisms.end(); it++)
	{
		delete *it;
	}
};
