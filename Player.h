#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <stack>
#include <iostream>
#include <unordered_map>

class Player
{
private:
	sf::RectangleShape snake;

	int length;
	int moveSpeed;
	std::vector<float> direction;
	sf::RectangleShape part;
	std::vector<sf::RectangleShape> body;
	std::vector<std::vector<int>> partPositions;
	std::stack<int> directionCache;
	std::unordered_map<int, std::vector<float>> bodyPartDirection;

	void initVariables();
	void initSnake();
	void growPart();

public:
	Player(float windowWidth, float windowHeight, float uiHeight);
	virtual ~Player();

	float positionX();
	float positionY();
	const sf::RectangleShape& getShape(int i) const;
	std::vector<std::vector<int>> getPartPositions(float uiHeight);
	int getLength();

	void updatePosition(float x, float y);
	void updateDirection();
	void updatePartDirection();
	void updateLength();

	void playerMove();
	void bodyMove(int i, std::vector<float> direction);
	bool touchingWindowBorder(sf::VideoMode videoMode, float uiHeight);
	bool checkBodyCollision();
	void wrapping(sf::VideoMode videoMode, float uiHeight);

	void render(sf::RenderTarget& target);
};

