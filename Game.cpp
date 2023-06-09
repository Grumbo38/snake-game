#include "Game.h"

void Game::initVariables()
{
	window = nullptr;
}

void Game::initWindow()
{
	uiHeight = 80;
	videoMode.height = 640 + uiHeight;
	videoMode.width = 640;

	window = new sf::RenderWindow(videoMode, "Snake");
	window->setFramerateLimit(144);
	window->setVerticalSyncEnabled(false);
	window->setKeyRepeatEnabled(false);
	readHighScore();
}

void Game::initPlayer()
{
	snake = new Player(videoMode.width, videoMode.height, uiHeight);
}

void Game::initApple()
{
	apple = new Apple(videoMode.width, videoMode.height, uiHeight);
}

void Game::initUI()
{
	ui = new UserInterface(videoMode.width, uiHeight);
	font.loadFromFile("Fonts/AldotheApache.ttf");
	controlsTexture.loadFromFile("Sprites/ARROW_KEYS_SPRITE.png");
	controlsTexture.setSmooth(true);
	controlsSprite.setTexture(controlsTexture);
	controlsSprite.setPosition(0, 0);
}

void Game::initText()
{
	scoreText.setFont(font);
	scoreText.setString("0");
	scoreText.setCharacterSize(40);
	scoreText.setPosition(70.f, 15.f);
	score = 0;

	tabToPauseText.setFont(font);
	tabToPauseText.setString("PRESS TAB TO PAUSE");
	tabToPauseText.setCharacterSize(30);
	tabToPauseText.setPosition(350.f, 5.f);

	escToQuitText.setFont(font);
	escToQuitText.setString("PRESS ESC TO QUIT");
	escToQuitText.setCharacterSize(30);
	escToQuitText.setPosition(350.f, 35.f);

	pausedText.setFont(font);
	pausedText.setString("PAUSED");
	pausedText.setCharacterSize(90);
	pausedText.setPosition(200.f, 300.f);
	
	keyToStartText.setFont(font);
	keyToStartText.setString("PRESS ANY KEY TO START");
	keyToStartText.setCharacterSize(40);
	keyToStartText.setPosition(135.f, 350.f);
	
	spaceToRetry.setFont(font);
	spaceToRetry.setString("PRESS ANY KEY TO RESTART");
	spaceToRetry.setCharacterSize(40);
	spaceToRetry.setPosition(135.f, 350.f);
}




Game::Game()
{
	initVariables();
	initWindow();
	initPlayer();
	initApple();
	initUI();
	initText();
	paused = false;
	start = false;
	gameOver = false;
}

Game::~Game()
{
	delete apple;
	delete snake;
	delete window;
}

const bool Game::running() const
{
	return window->isOpen();
}

void Game::pollEvents()
{
	while (window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
			{
				window->close();
			}
			else if ((ev.KeyPressed) && (start == false))
			{
				start = true;
			}
			else if ((ev.KeyPressed) && (gameOver == true))
			{
				delete apple;
				delete snake;

				initPlayer();
				initApple();
				initUI();
				initText();
				paused = false;
				start = false;
				gameOver = false;
			}
			else if ((ev.key.code == sf::Keyboard::Tab) && (paused == false))
			{
				paused = true;
			}
			else if ((ev.key.code == sf::Keyboard::Tab) && (paused == true))
			{
				paused = false;
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
	if (snake->getShape(0).getGlobalBounds().intersects(apple->getShape().getGlobalBounds()))
	{
		snake->updateLength();
		spawnApplePosition(uiHeight);
		updateScoreText();
	}
}

void Game::playerPlayercollision()
{
	if (snake->checkBodyCollision())
	{
		gameOver = true;
#ifdef NDEBUG
		updateHighScore(score);
#endif
	}
}

void Game::updatePlayer()
{
	snake->playerMove();
//	snake->wrapping(videoMode, uiHeight);
	if (snake->touchingWindowBorder(videoMode, uiHeight))
	{
		gameOver = true;
#ifdef NDEBUG
		updateHighScore(score);
#endif
	}
	snake->updatePartDirection();
	snake->updateDirection();
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
	highScoreText.setFont(font);
	highScoreText.setString("HIGH SCORE: " + i);
	highScoreText.setCharacterSize(30);
	highScoreText.setPosition(130.f, 23.f);
	if (!(i == ""))
	{
		highScore = std::stoi(i);
	}
}

void Game::updateScoreText()
{
	score++;
	scoreText.setString(std::to_string(score));
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
	window->clear();

	apple->render(*window);
	snake->render(*window);
	ui->render(*window);
	window->draw(scoreText);
	window->draw(tabToPauseText);
	window->draw(escToQuitText);
	window->draw(highScoreText);
	if (paused == true)
	{
		window->draw(pausedText);
	}
	if (start == false)
	{
		window->draw(keyToStartText);
	}
	if (gameOver == true)
	{
		window->draw(spaceToRetry);
	}
//	window->draw(controlsSprite);

	window->display();
}


