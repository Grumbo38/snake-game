#pragma once

#include <ctime>

#include "Player.h"
#include "Apple.h"
#include "UserInterface.h"
#include <iostream>
#include <string>
#include <fstream>

class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::Font font;
	sf::Text scoreText;
	sf::Text tabToPauseText;
	sf::Text escToQuitText;
	sf::Text pausedText;
	sf::Text keyToStartText;
	sf::Text spaceToRetry;
	sf::Text highScoreText;
	std::fstream highScore_file;
	sf::Texture controlsTexture;
	sf::Sprite controlsSprite;

	float uiHeight;
	bool paused;
	bool start;
	int score;
	int highScore;
	bool gameOver;

	Player* snake;
	Apple* apple;
	UserInterface* ui;

	void initVariables();
	void initWindow();
	void initPlayer();
	void initApple();
	void initUI();
	void initText();
	void readHighScore();

public:
	Game();
	virtual ~Game();

	const bool running() const;
	void pollEvents();

	void spawnApplePosition(float uiHeight);
	void playerAppleCollision();
	void playerPlayercollision();
	void updatePlayer();
	void updateScoreText();
	void updateHighScore(int newScore);
	void update();

	void render();
};