#ifndef ORDER_H_
#define ORDER_H_

#include "consts.hpp"

class Organism;

/*
 * A class for holding orders to be carried out by organisms
 */
class Order
{
public:
	Order(int a_x, int a_y, job a_job);
	Order();

	virtual int getX() const {return m_x;};
	virtual int getY() const {return m_y;};
	
	job getJob() {return m_job;};

private:
	int m_x;
	int m_y;

protected:
	job m_job;

};

#endif
