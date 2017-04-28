#include "graphics.hpp"

using namespace std;

Graphics::Graphics(int w, int h):
	window(sf::VideoMode(w, h), "Nifty Nature"),
	camX(0),
	camY(0)
{
	window.setFramerateLimit(30);
	
	// loading font
	font.loadFromFile("Sansation-Regular.ttf");
	
	// setting font
	text.setFont(font);
	
	// loading textures
	textures["bg"] = sf::Texture();
	textures["stone"] = sf::Texture();
	textures["grass"] = sf::Texture();
	textures["organism"] = sf::Texture();
	
	for(auto it = textures.begin(); it != textures.end(); it++)
	{
		std::string name = it->first;
		textures[name].loadFromFile(name + ".png");
	}
	
	bg.setTexture(textures["bg"]);
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
			continue;
			case sf::Keyboard::A:
				camX -= 16;
			continue;
			case sf::Keyboard::S:
				camY += 16;
			continue;
			case sf::Keyboard::D:
				camX += 16;
			continue;
			}
		break;
		case sf::Event::MouseButtonPressed:
			// drawing which position is currently being highlited
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			int mX = floor((mousePos.x + camX) / TILE_W);
			int mY = floor((mousePos.y + camY - OFFSET_Y) / TILE_H);
			printf("%i, %i, %i \n", mX, mY, (int)map[mX][mY][1]);
		break;
		}
	}
    
    // Drawing on screen
    
	window.clear();
	
	// DIRTY COLOUR (bg) IMPLEMENTATION
	for(int i = 0; i < 2; i++)
	{
		bg.setPosition( floor((i * SCREEN_W + camX) / SCREEN_W) * SCREEN_W - camX, 0);
		window.draw(bg);
	}
	
	// Drawing tiles
	for(int x = camX - TILE_W; x < camX + SCREEN_W + TILE_W; x += TILE_W)
	{
		for(int y = camY - TILE_H; y < camY + SCREEN_H + TILE_H; y += TILE_H)
		{
			int mapX = floor(x / TILE_W);
			int mapY = floor(y / TILE_H);
			
			if((mapX >= 0 && mapX < MAP_W && mapY >= 0 && mapY < MAP_H) && map[mapX][mapY][1] != none)
			{
				tile.setPosition(mapX*TILE_W - camX, mapY*TILE_H - camY + OFFSET_Y);
				if(map[mapX][mapY][1] == grass)
				{
					tile.setTexture(textures["grass"]);
				}
				else if(map[mapX][mapY][1] == stone)
				{
					tile.setTexture(textures["stone"]);
				}
				else
				{
					tile.setTexture(textures["void"]);
				}
				
				window.draw(tile);
			}
		}
	}
	
	// Drawing organisms
	for(auto it = organisms.begin(); it != organisms.end(); it++)
	{
		int x = (*it)->getX() * TILE_W - camX;
		int y = (*it)->getY() * TILE_H - camY + OFFSET_Y;
		
		tile.setPosition(x, y);
		tile.setTexture(textures["organism"]);
		window.draw(tile);
		
		text.setString(to_string((*it)->getEnergyPercentage()) + "%");
		text.setColor(sf::Color::Black);
		text.setPosition(x + 8, y - 16);
		window.draw(text);
	}
	
    window.display();
    
    return true;
}
