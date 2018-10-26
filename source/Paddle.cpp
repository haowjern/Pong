#include "stdafx.h"
#include "Paddle.h"
#include <iostream>


Paddle::Paddle(sf::Vector2f size, sf::Color colour, sf::Vector2f position, sf::Vector2f origin)
{

	this->setSize(size);
	this->setFillColor(colour);
	this->setPosition(position);
	this->setOrigin(origin);

	// ensures with any origin bounds can be made correctly
	sf::Vector2f fraction;
	fraction.x = origin.x / size.x;
	fraction.y = origin.y / size.y;

	rightBound = position.x + (1 - fraction.x)*size.x;
	leftBound = position.x - fraction.x*size.x;
	upperBound = position.y - fraction.y*size.y;
	lowerBound = position.y + (1 - fraction.y)*size.y;
}

void Paddle::updateBounds()
{
	sf::Vector2f position(this->getPosition());
	sf::Vector2f origin(this->getOrigin());
	sf::Vector2f size(this->getSize()); 

	sf::Vector2f fraction; 
	fraction.x = origin.x / size.x;
	fraction.y = origin.y / size.y; 

	rightBound = position.x + (1 - fraction.x)*size.x;
	leftBound = position.x - fraction.x*size.x;
	upperBound = position.y - fraction.y*size.y;
	lowerBound = position.y + (1- fraction.y)*size.y;
}

Paddle::~Paddle()
{
}
