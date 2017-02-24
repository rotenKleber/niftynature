#include "graphics.hpp"

using namespace std;

Graphics::Graphics(int w, int h):
	window(sf::VideoMode(w, h), "Nifty Nature"),
	tile(sf::Vector2f(TILE_W, TILE_W)),
	camX(0),
	camY(0)
{
	window.setFramerateLimit(30);
}

Graphics::~Graphics()
{
}


// Returns false if there is a closing event
bool Graphics::update(terrain (&map)[MAP_W][MAP_H][2], list<Organism*> &organisms)
{
	// Polling events
	sf::Event event;
	while(window.pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::Closed:
			window.close();
			return false;
		break;
		case sf::Event::KeyPressed:
			switch(event.key.code)
			{
			case sf::Keyboard::W:
				camY -= 16;
			break;
			case sf::Keyboard::A:
				camX -= 16;
			break;
			case sf::Keyboard::S:
				camY += 16;
			break;
			case sf::Keyboard::D:
				camX += 16;
			break;
			}
		break;
		}
	}
    
    // Drawing on screen
	window.clear();
	
	// Drawing tiles
	for(int x = camX - TILE_W; x < camX + SCREEN_W + TILE_W; x += TILE_W)
	{
		for(int y = camY - TILE_H; y < camY + SCREEN_H + TILE_H; y += TILE_H)
		{
			int mapX = round(x / TILE_W);
			int mapY = round(y / TILE_H);
			
			tile.setPosition(mapX*TILE_W - camX, mapY*TILE_H - camY);
			if(map[mapX][mapY][1] == grass)
			{
				tile.setFillColor(sf::Color::Green);
			}
			else if(map[mapX][mapY][1] == stone)
			{
				tile.setFillColor(sf::Color::Magenta);
			}
			else
			{
				tile.setFillColor(sf::Color::Yellow);
			}
			
			window.draw(tile);
		}
	}
	
	// Drawing organisms
	for(auto it = organisms.begin(); it != organisms.end(); it++)
	{
		tile.setPosition((*it)->getX() * TILE_W - camX, (*it)->getY() * TILE_H - camY);
		tile.setFillColor(sf::Color::Red);
		window.draw(tile);
	}
	
    window.display();
    
    return true;
}
