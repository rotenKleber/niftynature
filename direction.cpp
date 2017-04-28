#include "direction.hpp"
#include "consts.hpp"

cardinal Direction::getRandParallel(cardinal dir)
{
	switch(dir)
	{
	case LEFT:
	case RIGHT:
	
	return (irandom(0, 1) == 0 ? UP : DOWN);
	
	break;
	case UP:
	case DOWN:
	
	return (irandom(0, 1) == 0 ? RIGHT : LEFT);
	
	break;
	default:
		return CENTRE;
	break;
	}
}

cardinal Direction::getOpposite(cardinal dir)
{
	switch(dir)
	{
	case LEFT:
		return RIGHT;
	break;
	case RIGHT:
		return LEFT;
	break;
	case UP:
		return DOWN;
	break;
	case DOWN:
		return UP;
	break;
	default:
		return CENTRE;
	break;
	}
}

cardinal Direction::getBestParallel(cardinal dir, int delta)
{
	switch(dir)
	{
	case LEFT:
	case RIGHT:
	
	return (delta < 0 ? UP : DOWN);
	
	break;
	case UP:
	case DOWN:
	
	return (delta > 0 ? RIGHT : LEFT);
	
	break;
	default:
		return CENTRE;
	break;
	}
}

int Direction::dec(cardinal dir)
{
	switch(dir)
	{
	case LEFT:
		return -1;
	break;
	case RIGHT:
		return 1;
	break;
	case DOWN:
		return 1;
	break;
	case UP:
		return -1;
	break;
	default:
		return 0;
	break;
	}
}
