#pragma once
#include <SFML\Graphics.hpp>
#include "Collidable.h"
class Ball : public sf::CircleShape, public Collidable
{
public:
	Ball(float radius, sf::Color colour, sf::Vector2f position, sf::Vector2f origin);
	~Ball();

	void updateBounds();
};

