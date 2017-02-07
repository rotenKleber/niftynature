#ifndef GRAPIHCS_H_
#define GRAPIHCS_H_

#include "consts.hpp"
#include <list>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "organism.hpp"

using namespace std;

class Graphics
{
public:
	Graphics(int w, int h);
	~Graphics();
	
	bool update(terrain (&map)[MAP_W][MAP_H], list<Organism*> &organisms);
	
private:
	sf::RenderWindow window;
	
	sf::RectangleShape tile;
	
};

#endif
