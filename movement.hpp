#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "direction.hpp"

class Movement
{
public:
	Movement(cardinal a, cardinal s);
	cardinal attempted;
	cardinal substituted;

};

#endif
