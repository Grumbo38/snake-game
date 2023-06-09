#include "UserInterface.h"

void UserInterface::initUI(float windowWidth, float uiHeight)
{
	ui.setFillColor(sf::Color(0, 0, 80, 255));
	ui.setSize(sf::Vector2f(windowWidth, uiHeight));
	ui.setOutlineThickness(3.f);
	ui.setOutlineColor(sf::Color(0, 0, 40, 255));
	ui.setPosition(0, 0);

	appleScoreUi.setSize(sf::Vector2f(25.f, 25.f)); //must be multiples of 20 for perfect 16:9
	appleScoreUi.setFillColor(sf::Color::Red);
	appleScoreUi.setOutlineThickness(0.f);
	appleScoreUi.setOutlineColor(sf::Color(139, 0, 0, 0));
	appleScoreUi.setPosition(35.f, 30.f);
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
	target.draw(ui);
	target.draw(appleScoreUi);
}
