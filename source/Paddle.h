#pragma once
#include <SFML\Graphics.hpp>
#include "Collidable.h"

class Paddle : public sf::RectangleShape,  public Collidable
{
public:
	Paddle(sf::Vector2f size, sf::Color colour, sf::Vector2f position, sf::Vector2f origin);
	~Paddle();

	void updateBounds();
};

