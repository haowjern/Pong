#include "stdafx.h"
#include "Ball.h"
#include <SFML\Graphics.hpp>
#include "Collidable.h"

Ball::Ball(float radius, sf::Color colour, sf::Vector2f position, sf::Vector2f origin)
{
	this->setRadius(radius);
	this->setFillColor(colour);
	this->setOrigin(origin);
	this->setPosition(position); 

	// ensures with any origin bounds can be made correctly
	sf::Vector2f fraction;
	fraction.x = origin.x / radius;
	fraction.y = origin.y / radius;

	rightBound = position.x + (1 - fraction.x)*radius;
	leftBound = position.x - fraction.x*radius;
	upperBound = position.y - fraction.y*radius;
	lowerBound = position.y + (1 - fraction.y)*radius;
}

Ball::~Ball()
{
}

void Ball::updateBounds()
{
	sf::Vector2f position(this->getPosition());
	sf::Vector2f origin(this->getOrigin());
	float radius (this->getRadius());

	sf::Vector2f fraction;
	fraction.x = origin.x / radius;
	fraction.y = origin.y / radius;

	rightBound = position.x + (1 - fraction.x)*radius;
	leftBound = position.x - fraction.x*radius;
	upperBound = position.y - fraction.y*radius;
	lowerBound = position.y + (1 - fraction.y)*radius;
}
