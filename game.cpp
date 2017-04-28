#include "game.hpp"

Game::Game() 
{
	srand(time(NULL));
	
	for(int xx = 0; xx < MAP_W; xx++)
	{
		for(int yy = 0; yy < MAP_H; yy++)
		{
			if (irandom(0, 32) == 0)
			{
				map[xx][yy][1] = stone;
			}
			else if(irandom(0, 1) == 0)
			{
				map[xx][yy][1] = grass;
			}
			else
			{
				map[xx][yy][1] = none;
			}
		}
	}
}


// method to move an organism
// takes a turn for each organism
bool Game::move(Organism* it)
{
	Organism& o = *it;
	
	// Movement
	if(o.memory.empty())
	{
		// ran if memory is empty
		
		if(!o.orders.empty())
		{	
			// establish the delta x and y for the destination and current coords
			int dX = o.orders.front()->getX() - o.getX();
			int dY = o.orders.front()->getY() - o.getY();
						
			if(abs(dX) > abs(dY))
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
		// ran if there are movements recorded in memory
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
				int dY = o.orders.front()->getY() - o.getY();
				int dX = o.orders.front()->getX() - o.getX();
				
				if(dY == dX)
				{
					// Moves at parallel movement towards target (randomly chosen)
					o.memory.push(Movement(substituted, Direction::getRandParallel(substituted)));
					move(it);
				}
				else
				{
					if(attempted == LEFT || attempted == RIGHT)
					{
						// Moves at parallel movement towards target (y direction)
						o.memory.push(Movement(substituted, Direction::getBestParallel(substituted, dY)));
						move(it);
					}
					else
					{
						// Moves at parallel movement towards target (x direction)
						o.memory.push(Movement(substituted, Direction::getBestParallel(substituted, dX)));
						move(it);
					}
				}
			}
			else
			{
				o.memory.push(Movement(substituted, Direction::getOpposite(attempted)));
				move(it);
			}
		}
		else
		{
			// whether or not the memory has been cleared
			bool clearedMem = false;
			
			int dX, dY;
			// check to see if at position, and remove order if complete
			dX = o.orders.front()->getX() - o.getX();
			dY = o.orders.front()->getY() - o.getY();
			
			if(dX == 0 && dY == 0)
			{				
				// perform the job now
				performJob(it, o.orders.front()->getJob());		
				
				delete o.orders.front();	
				
				// remove order
				o.orders.pop_front();
							
				// Clearing memory of previous movements
				while(!o.memory.empty())
				{
					o.memory.pop();
				}
				
				clearedMem = true;
				}
			
			if(!clearedMem)
				o.memory.pop(); // remove last movement memory if move has been completed
		}
	}
	
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
		Organism* o = *it;
		
		if(move(o))
		{	

			// Free organism
			delete o;

			// Remove it from the list
			// And reset iterator
			it = organisms.erase(it);

			// setting organism to nullptr
			o = nullptr;
			
			// return to break method (organism is dead)
			return;
		}
		
		// also checking to see if hungry
		if(o->orders.size() == 0)
		{
			if(o->isHungry())
			{
				std::pair<int, int> pos = getNearestTerrain(o->getX(), o->getY(), grass);
				
				// checking to see if it's null
				if(pos.first != -1 || pos.second != -1)
				{
					if(o->orders.size() <= 1)
					{
						o->addOrder(pos.first, pos.second, eat);
					}
				}
			}
		}
		
		o->takeTurn();
	}
}

bool Game::isFree(int x, int y)
{
	if(x >= 0 && x < MAP_W && y >= 0 && y < MAP_H)
	{
		if(map[x][y][1] != stone)
		{
			return true;
		}
	}

	return false;
}

void Game::performJob(Organism* o, job j)
{	
	int x = o->getX();
	int y = o->getY();
	
	switch(j)
	{
	case eat:
		if(map[x][y][1] == grass)
		{
			map[x][y][1] = none;
			
			o->eat(cellulose, 15);
		}
	break;
	}
	
	// also checking to see if hungry
	if(o->orders.size() <= 1)
	{
		if(o->isHungry())
		{
			std::pair<int, int> pos = getNearestTerrain(o->getX(), o->getY(), grass);
			
			// checking to see if it's null
			if(pos.first == -1 || pos.second == -1)
				return;
			
			if(o->orders.size() <= 1)
			{
				o->addOrder(pos.first, pos.second, eat);
			}
		}
	}
}

Game::~Game()
{
	for(auto it = organisms.begin(); it != organisms.end(); it++)
	{
		delete *it;
	}
}

std::pair<int, int> Game::getNearestTerrain(int x, int y, terrain t)
{
	// setting the position to the default (-1, -1)
	std::pair<int, int> pos;
	pos.first = -1;
	pos.second = -1;
	
	for(int r = 1; r <= 10; r++)
	{		
		// checking for the columns
		for(int xx = -r; xx <= r; xx += 2*r)
		{
			for(int yy = -r; yy <= r; yy++)
			{
				if(map[xx+x][yy+y][1] == t && xx+x >= 0 && xx+x < MAP_W && yy+y >= 0 && yy+y < MAP_H)
				{
					pos.first = xx+x;
					pos.second = yy+y;
					
					return pos;
				}
			}
		}
		
		// checking for the rows
		for(int yy = -r; yy <= r; yy += 2*r)
		{
			for(int xx = -r; xx <= r; xx++)
			{
				if(map[xx+x][yy+y][1] == t && xx+x >= 0 && xx+x < MAP_W && yy+y >= 0 && yy+y < MAP_H)
				{
					pos.first = xx+x;
					pos.second = yy+y;
					
					return pos;
				}
			}
		}
	}
	return pos;
}

// returns a reference to the pointer of the nearest herbivore to position (x, y)
Organism** Game::getNearestHerbivore(int x, int y, terrain t)
{
	Organism **o;
	
	std::pair<int, Organism**> minSquared;
	
	// beginning loop to cycle throughout organisms and set the smaller ones to the minimum
	auto it = organisms.begin();
	minSquared.first = pow((*it)->getX() - x, 2) + pow((*it)->getY() - y, 2);
	minSquared.second = &(*it);
	
	for(it++; it != organisms.end(); it++)
	{
		int distanceSquared = pow((*it)->getX() - x, 2) + pow((*it)->getY() - y, 2);
		
		if(distanceSquared < minSquared.first)
		{
			minSquared.first = distanceSquared;
			minSquared.second = &(*it);
		} 
	}
	
	
	return o;
}
