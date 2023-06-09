#pragma once

#include "Player.h"

class Apple
{
private:
	sf::RectangleShape apple;
	
	void initVariables();
	void initApple();

public:
	Apple(float windowWidth, float windowHeight, float uiHeight);
	virtual ~Apple();

	const sf::RectangleShape& getShape() const;

	void updatePosition(float x, float y);
	void update();
	void render(sf::RenderTarget& target);
};

