#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->uiHeight = 80;
	this->videoMode.height = 640 + uiHeight;
	this->videoMode.width = 640;

	this->window = new sf::RenderWindow(this->videoMode, "Snake");
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
	this->window->setKeyRepeatEnabled(false);
	readHighScore();
}

void Game::initPlayer()
{
	this->snake = new Player(videoMode.width, videoMode.height, uiHeight);
}

void Game::initApple()
{
	this->apple = new Apple(videoMode.width, videoMode.height, uiHeight);
}

void Game::initUI()
{
	this->ui = new UserInterface(videoMode.width, uiHeight);
	this->font.loadFromFile("Fonts/AldotheApache.ttf");
	this->controlsTexture.loadFromFile("Sprites/ARROW_KEYS_SPRITE.png");
	this->controlsTexture.setSmooth(true);
	this->controlsSprite.setTexture(this->controlsTexture);
	this->controlsSprite.setPosition(0, 0);
}

void Game::initText()
{
	this->scoreText.setFont(font);
	this->scoreText.setString("0");
	this->scoreText.setCharacterSize(40);
	this->scoreText.setPosition(70.f, 15.f);
	this->score = 0;

	this->tabToPauseText.setFont(font);
	this->tabToPauseText.setString("PRESS TAB TO PAUSE");
	this->tabToPauseText.setCharacterSize(30);
	this->tabToPauseText.setPosition(350.f, 5.f);

	this->escToQuitText.setFont(font);
	this->escToQuitText.setString("PRESS ESC TO QUIT");
	this->escToQuitText.setCharacterSize(30);
	this->escToQuitText.setPosition(350.f, 35.f);

	this->pausedText.setFont(font);
	this->pausedText.setString("PAUSED");
	this->pausedText.setCharacterSize(90);
	this->pausedText.setPosition(200.f, 300.f);
	
	this->keyToStartText.setFont(font);
	this->keyToStartText.setString("PRESS ANY KEY TO START");
	this->keyToStartText.setCharacterSize(40);
	this->keyToStartText.setPosition(135.f, 350.f);
	
	this->spaceToRetry.setFont(font);
	this->spaceToRetry.setString("PRESS ANY KEY TO RESTART");
	this->spaceToRetry.setCharacterSize(40);
	this->spaceToRetry.setPosition(135.f, 350.f);
}




Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initPlayer();
	this->initApple();
	this->initUI();
	this->initText();
	this->paused = false;
	this->start = false;
	this->gameOver = false;
}

Game::~Game()
{
	delete this->apple;
	delete this->snake;
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			else if ((ev.KeyPressed) && (start == false))
			{
				this->start = true;
			}
			else if ((ev.KeyPressed) && (gameOver == true))
			{
				delete this->apple;
				delete this->snake;

				this->initPlayer();
				this->initApple();
				this->initUI();
				this->initText();
				this->paused = false;
				this->start = false;
				this->gameOver = false;
			}
			else if ((ev.key.code == sf::Keyboard::Tab) && (paused == false))
			{
				this->paused = true;
			}
			else if ((ev.key.code == sf::Keyboard::Tab) && (paused == true))
			{
				this->paused = false;
			}
			break;
		}
	}
}

void Game::spawnApplePosition(float uiHeight)
{
	std::vector<std::vector<int>> partPositions;
	partPositions = this->snake->getPartPositions(uiHeight);
	int x, y;
	x = (rand() % static_cast<int>(videoMode.width / 20));
	y = (rand() % static_cast<int>((videoMode.height - uiHeight) / 20));
	for (auto& p : partPositions)
	{
		if (x == p[0] && y == p[1])
		{
			spawnApplePosition(uiHeight);
		}
	}
	apple->updatePosition(static_cast<float>(x * 20), static_cast<float>(y * 20) + uiHeight);
}

void Game::playerAppleCollision()
{
	if (this->snake->getShape(0).getGlobalBounds().intersects(this->apple->getShape().getGlobalBounds()))
	{
		this->snake->updateLength();
		spawnApplePosition(uiHeight);
		updateScoreText();
	}
}

void Game::playerPlayercollision()
{
	if (this->snake->checkBodyCollision())
	{
		gameOver = true;
		updateHighScore(score);
	}
}

void Game::updatePlayer()
{
	this->snake->playerMove();
//	this->snake->wrapping(videoMode, uiHeight);
	if (this->snake->touchingWindowBorder(videoMode, uiHeight))
	{
		gameOver = true;
		updateHighScore(score);
	}
	this->snake->updatePartDirection();
	this->snake->updateDirection();
}

void Game::readHighScore()
{
	highScore_file.open("high-score.txt", std::ios::in);
	std::string i;
	while (true)
	{
		highScore_file >> i;
		if (highScore_file.eof())
		{
			break;
		}
	}
	this->highScoreText.setFont(font);
	this->highScoreText.setString("HIGH SCORE: " + i);
	this->highScoreText.setCharacterSize(30);
	this->highScoreText.setPosition(130.f, 23.f);
	if (!(i == ""))
	{
		this->highScore = std::stoi(i);
	}
}

void Game::updateScoreText()
{
	score++;
	this->scoreText.setString(std::to_string(score));
}

void Game::updateHighScore(int newScore)
{
	if (newScore > highScore)
	{
		highScore_file.open("high-score.txt", std::ios::trunc);
		highScore_file.close();
		highScore_file.open("high-score.txt", std::ios::out);
		highScore_file << std::to_string(newScore);
		highScore_file.close();
		readHighScore();
	}
	
}

void Game::update()
{
	if (start == false)
	{
		pollEvents();
	}
	else if (gameOver == true)
	{
		pollEvents();
	}
	else if (paused == true)
	{
		pollEvents();
	}
	else if (window->hasFocus())
	{
		pollEvents();
		updatePlayer();
		playerAppleCollision();
		playerPlayercollision();
	}
	else
	{
		pollEvents();
	}
}

void Game::render()
{
	this->window->clear();

	this->apple->render(*this->window);
	this->snake->render(*this->window);
	this->ui->render(*this->window);
	this->window->draw(scoreText);
	this->window->draw(tabToPauseText);
	this->window->draw(escToQuitText);
	this->window->draw(highScoreText);
	if (paused == true)
	{
		this->window->draw(pausedText);
	}
	if (start == false)
	{
		this->window->draw(keyToStartText);
	}
	if (gameOver == true)
	{
		this->window->draw(spaceToRetry);
	}
//	this->window->draw(controlsSprite);

	this->window->display();
}


