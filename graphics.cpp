#include "graphics.hpp"

using namespace std;

Graphics::Graphics(int w, int h):
	window(sf::VideoMode(w, h), "Nifty Nature"),
	tile(sf::Vector2f(32, 32))
{
	window.setFramerateLimit(30);
}

Graphics::~Graphics()
{
}


// Returns false if there is a closing event
bool Graphics::update(terrain (&map)[MAP_W][MAP_H], list<Organism*> &organisms)
{
	// Polling events
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			return false;
		}
	}
    
    // Drawing on screen
	window.clear();
	
	// Drawing tiles
	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			tile.setPosition(x * 32, y * 32);
			if(map[x][y] == grass)
				tile.setFillColor(sf::Color::Green);
			else
				tile.setFillColor(sf::Color::Yellow);
				
			window.draw(tile);
		} 
	}
	
	// Drawing organisms
	for (auto it = organisms.begin(); it != organisms.end(); it++)
	{
		tile.setPosition((*it)->getX() * 32, (*it)->getY() * 32);
		tile.setFillColor(sf::Color::Red);
		window.draw(tile);
	}
	
    window.display();
    
    return true;
}
