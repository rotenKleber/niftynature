#ifndef ORDERTARGET_H_
#define ORDERTARGET_H_

#include "consts.hpp"
#include "order.hpp"
#include "organism.hpp"

class Organism;

/*
 * A class for holding orders to be carried out by organisms
 */
class OrderTarget : public Order
{
public:
	OrderTarget(Organism **o, job a_job);
	
	int getX() const;
	int getY() const;
	
//private:
	Organism **target;
	
protected:
	job m_job;
};

#endif
