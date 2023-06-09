#include "UserInterface.h"

void UserInterface::initUI(float windowWidth, float uiHeight)
{
	this->ui.setFillColor(sf::Color(0, 0, 80, 255));
	this->ui.setSize(sf::Vector2f(windowWidth, uiHeight));
	this->ui.setOutlineThickness(3.f);
	this->ui.setOutlineColor(sf::Color(0, 0, 40, 255));
	this->ui.setPosition(0, 0);

	this->appleScoreUi.setSize(sf::Vector2f(25.f, 25.f)); //must be multiples of 20 for perfect 16:9
	this->appleScoreUi.setFillColor(sf::Color::Red);
	this->appleScoreUi.setOutlineThickness(0.f);
	this->appleScoreUi.setOutlineColor(sf::Color(139, 0, 0, 0));
	this->appleScoreUi.setPosition(35.f, 30.f);
}

UserInterface::UserInterface(float windowWidth, float uiHeight)
{
	initUI(windowWidth, uiHeight);
}

UserInterface::~UserInterface()
{
}

void UserInterface::render(sf::RenderTarget& target)
{
	target.draw(this->ui);
	target.draw(this->appleScoreUi);
}
