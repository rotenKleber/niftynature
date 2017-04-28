#ifndef DIRECTION_H_
#define DIRECTION_H_

enum cardinal {CENTRE, RIGHT, UP, LEFT, DOWN};

class Direction
{
public:	
	static cardinal getRandParallel(cardinal dir);
	static cardinal getOpposite(cardinal dir);
	static cardinal getBestParallel(cardinal dir, int delta);
	static int dec(cardinal dir);
};

#endif
