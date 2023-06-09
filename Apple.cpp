#include "Apple.h"
#include <iostream>

void Apple::initVariables()
{

}

void Apple::initApple()
{
	this->apple.setSize(sf::Vector2f(20.f, 20.f)); //must be multiples of 20 for perfect 16:9
	this->apple.setFillColor(sf::Color::Red);
	this->apple.setOutlineThickness(0.f);
	this->apple.setOutlineColor(sf::Color(139, 0, 0, 0));
}

Apple::Apple(float windowWidth, float windowHeight, float uiHeight)
{
	this->initVariables();
	this->initApple();
	float x, y;
	x = static_cast<float>((rand() % static_cast<int>(windowWidth / 20)) * 20);
	y = uiHeight + static_cast<float>((rand() % static_cast<int>((windowHeight - uiHeight) / 20)) * 20);
	this->apple.setPosition(x, y);
}

Apple::~Apple()
{

}

const sf::RectangleShape& Apple::getShape() const
{
	return apple;
}

void Apple::updatePosition(float x, float y)
{
	apple.setPosition(x, y);
}

void Apple::update()
{

}

void Apple::render(sf::RenderTarget& target)
{
	target.draw(this->apple);
}
