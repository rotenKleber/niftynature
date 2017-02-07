#ifndef ORGANISM_H_
#define ORGANISM_H_

#include "consts.hpp"
#include <string>

using namespace std;

class Organism
{
public:
	Organism(int code[nTraits]);
	Organism();

	static Organism repopulate(Organism &org1, Organism &org2);

	int (&getCode())[nTraits] {return m_code;};
	int getX() const {return m_x;};
	int getY() const {return m_y;};

	bool takeTurn();
	void eat(const food &type, const int &rawEnergy);
	void move(const int &x, const int &y);
	void setPosition(int x, int y) {m_x = x; m_y = y;};

private:
	int m_code[nTraits];
	unsigned int m_energy;
	unsigned int m_health;
	unsigned int m_combat;
	
	int m_x, m_y;
	
};

#endif
