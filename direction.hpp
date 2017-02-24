#ifndef DIRECTION_H_
#define DIRECTION_H_

enum cardinal {CENTRE, RIGHT, UP, LEFT, DOWN};

class Direction
{
public:	
	static cardinal getParallel(cardinal dir);
	static cardinal getOpposite(cardinal dir);
	static int dec(cardinal dir);
};

#endif
