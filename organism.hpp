#ifndef ORGANISM_H_
#define ORGANISM_H_

#include "consts.hpp"
#include "movement.hpp"
#include <string>
#include <stack>

using namespace std;

class Organism
{
public:
	Organism(int code[nTraits]);
	Organism();

	static Organism repopulate(Organism &org1, Organism &org2);

	int (&getCode())[nTraits] {return m_code;};
	int getEnergy() const {return m_energy;};
	int getX() const {return m_x;};
	int getY() const {return m_y;};
	int getTargetX() const {return m_targetX;};
	int getTargetY() const {return m_targetY;};
	bool hasTarget() const {return m_hasTarget;};
	bool isHungry() const;

	bool takeTurn();
	void eat(const food &type, const int &rawEnergy);
	void move(const int &x, const int &y);
	void setPosition(int x, int y) {m_x = x; m_y = y;};
	void setTarget(int x, int y) {m_targetX = x; m_targetY = y;};
	bool setHasTarget(bool hasTarget) {m_hasTarget = hasTarget;};

	stack<Movement> memory;
	
private:
	int m_code[nTraits];
	unsigned int m_energy, m_maxEnergy;
	unsigned int m_health;
	unsigned int m_combat;
	
	bool m_hasTarget;
	
	int m_x, m_y;
	int m_targetX, m_targetY;
	
};

#endif
