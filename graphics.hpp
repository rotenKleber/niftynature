#ifndef GRAPIHCS_H_
#define GRAPIHCS_H_

#include "consts.hpp"
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "organism.hpp"
#include "ordertarget.hpp"


using namespace std;

class Graphics
{
public:
	Graphics(int w, int h);
	~Graphics();
	
	bool update(terrain (&map)[MAP_W][MAP_H][2], list<Organism*> &organisms);
	
private:
	int camX, camY;
	
	std::unordered_map<std::string, sf::Texture> textures;

	sf::RenderWindow window;
	
	sf::Sprite tile;
	sf::Sprite bg;
	sf::Text text;
	
	sf::Font font;
	
};

#endif
