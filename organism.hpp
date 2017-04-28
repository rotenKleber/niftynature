#ifndef ORGANISM_H_
#define ORGANISM_H_

#include "consts.hpp"
#include "movement.hpp"
#include "order.hpp"
#include <string>
#include <stack>
#include <deque>

using namespace std;

/*
 * Class for each and every organism
 */

class Organism
{
public:
	Organism(int code[nTraits]);
	Organism();
	~Organism();
	
	static Organism repopulate(Organism &org1, Organism &org2);
	
	int (&getCode())[nTraits] {return m_code;};
	int getEnergy() const {return m_energy;};
	int getMaxEnergy() const {return m_maxEnergy;};
	int getEnergyPercentage() const {return int( ((float) m_energy / (float) m_maxEnergy) * 100 );};
	int getX() const {return m_x;};
	int getY() const {return m_y;};
	bool isHungry() const;
	
	bool takeTurn();
	void eat(const food &type, const int &rawEnergy);
	void move(const int &x, const int &y);
	void setPosition(int x, int y) {m_x = x; m_y = y;};
	
	void addOrder(int x, int y, job j) {orders.push_back(new Order(x, y, j));};
	//void addOrderTarget(Organism** o, job j) {};
	
	stack<Movement> memory;
	deque<Order*> orders;
	
private:
	int m_code[nTraits];
	unsigned int m_energy, m_maxEnergy;
	unsigned int m_health;
	unsigned int m_combat;
	
	int m_x, m_y;
	
};

#endif
