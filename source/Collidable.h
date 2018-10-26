#pragma once
class Collidable
{
public:
	Collidable();
	~Collidable();

	bool checkCollision(const Collidable& collidable); // returns true if collided with another collidable object
	// function only works to check collision between objects that arrive at each other sideways, not from the top / bottom 
	// will implemnt more if needed 

	bool checkCollision_topbtm(float bottom_wall);

	bool checkCollision_leftright(float right_wall);

	void virtual updateBounds() = 0;

//protected:
public:
	float lowerBound;
	float upperBound;
	float leftBound;
	float rightBound;
};




