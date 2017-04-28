#include "ordertarget.hpp"

OrderTarget::OrderTarget(Organism **o, job a_job):
	Order(),
	target(o),
	m_job(a_job)
{
}

int OrderTarget::getX() const
{
	// checking to make sure organism still exists
	if((*target) != nullptr)
	{
		return (*target)->getX();
	}
	
	printf("NULL ORGANISM\n");
	return 0;
}

int OrderTarget::getY() const
{
	// checking to make sure organism still exists
	if((*target) != nullptr)
	{
		return (*target)->getY();
	}
	
	printf("NULL ORGANISM\n");
	return 0;
}
