#include "stdafx.h"
#include "Collidable.h"
#include "SFML\Graphics.hpp"


Collidable::Collidable()
{
}


Collidable::~Collidable()
{
}

bool Collidable::checkCollision(const Collidable& collidable)
{
	if ((rightBound > collidable.leftBound) && (leftBound < collidable.rightBound)) // if hits one side
	{
		if ((upperBound < collidable.lowerBound) && (lowerBound > collidable.upperBound)) // and inside the top bottom boundary
		{
			return true;
		}
	}

	return false;
}

bool Collidable::checkCollision_topbtm(float bottom_wall)
{
	if ((upperBound < 0) || (lowerBound > bottom_wall))
	{
		return true;
	}

	return false; 
}


bool Collidable::checkCollision_leftright(float right_wall)
{
	if ((leftBound < 0) || (rightBound > right_wall))
	{
		return true;
	}

	return false;
}