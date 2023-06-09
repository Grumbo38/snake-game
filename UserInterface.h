#pragma once
#include "Player.h"

class UserInterface
{
private:
	sf::RectangleShape ui;
	sf::RectangleShape appleScoreUi;

	void initUI(float windowWidth, float uiHeight);

public:
	UserInterface(float windowWidth, float uiHeight);
	virtual ~UserInterface();

	void render(sf::RenderTarget& target);
};

