#include "Player.h"

void Player::initVariables()
{
	this->length = 2;
	this->moveSpeed = 2;
	this->direction = {1.f, 0.f};
}

void Player::initSnake()
{
	this->snake.setFillColor(sf::Color::Green);
	this->snake.setSize(sf::Vector2f(20.f, 20.f));
	this->snake.setOutlineThickness(0.f);
	this->snake.setOutlineColor(sf::Color(0, 128, 128, 255));
	this->part.setFillColor(sf::Color::Green);
	this->part.setSize(sf::Vector2f(20.f, 20.f));
	this->part.setOutlineThickness(0.f);
	this->part.setOutlineColor(sf::Color(0, 128, 128, 255));
	this->body.push_back(snake);
	this->body.push_back(part);
	this->bodyPartDirection[0] = this->direction;
	this->bodyPartDirection[1] = this->direction;
}

void Player::growPart()
{
	this->body.push_back(part);
	this->body[length - 1].setPosition(body[length - 2].getPosition().x - (20.f * bodyPartDirection[length - 2][0]), body[length - 2].getPosition().y - (20.f * bodyPartDirection[length - 2][1]));
	this->bodyPartDirection[length - 1] = bodyPartDirection[length - 2];
}

Player::Player(float windowWidth, float windowHeight, float uiHeight)
{
	this->initVariables();
	this->initSnake();
	float x, y;
	x = static_cast<float>((rand() % static_cast<int>(windowWidth / 20)/2) * 20);
	y = uiHeight + static_cast<float>((rand() % static_cast<int>((windowHeight - uiHeight) / 20)) * 20);
	this->body[0].setPosition(x, y);
	this->body[1].setPosition(x - 20.f, y);
}

Player::~Player()
{

}

float Player::positionX()
{
	return this->body[0].getPosition().x;
}

float Player::positionY()
{
	return this->body[0].getPosition().y;
}

const sf::RectangleShape& Player::getShape(int i) const
{
	return body[i];
}

std::vector<std::vector<int>> Player::getPartPositions(float uiHeight)
{
	partPositions.clear();
	for (auto& p : body)
	{
		partPositions.push_back({ static_cast<int>(p.getPosition().x / 20), static_cast<int>(uiHeight)/20 + static_cast<int>(p.getPosition().y / 20) });
	}
	
	return partPositions;
}

int Player::getLength()
{
	return length;
}

void Player::updatePosition(float x, float y)
{
	body[0].setPosition(x, y);
}

void Player::updateDirection()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
	{

	}
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
	{

	}

	else if (directionCache.empty())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (bodyPartDirection[0][0] == 1.f || bodyPartDirection[0][0] == -1.f))
		{
			if (static_cast<int>(body[0].getPosition().x) % 20 == 0)
			{
				bodyPartDirection[0] = { 0.f, -1.f };
			}
			else 
			{
				directionCache.push(1);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (bodyPartDirection[0][1] == 1.f || bodyPartDirection[0][1] == -1.f))
		{
			if (static_cast<int>(body[0].getPosition().y) % 20 == 0)
			{
				bodyPartDirection[0] = { 1.f, 0.f };
			}
			else
			{
				directionCache.push(2);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (bodyPartDirection[0][0] == 1.f || bodyPartDirection[0][0] == -1.f))
		{
			if (static_cast<int>(body[0].getPosition().x) % 20 == 0)
			{
				bodyPartDirection[0] = { 0.f, 1.f };
			}
			else
			{
				directionCache.push(3);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (bodyPartDirection[0][1] == 1.f || bodyPartDirection[0][1] == -1.f))
		{
			if (static_cast<int>(body[0].getPosition().y) % 20 == 0)
			{
				bodyPartDirection[0] = { -1.f, 0.f };
			}
			else
			{
				directionCache.push(4);
			}
		}
	}
	
	else if(static_cast<int>(body[0].getPosition().x) % 20 == 0 && static_cast<int>(body[0].getPosition().y) % 20 == 0)
	{
		switch (directionCache.top())
		{
		case 1:
			bodyPartDirection[0] = { 0.f, -1.f };
			directionCache.pop();
			break;
		case 2:
			bodyPartDirection[0] = { 1.f, 0.f };
			directionCache.pop();
			break;
		case 3:
			bodyPartDirection[0] = { 0.f, 1.f };
			directionCache.pop();
			break;
		case 4:
			bodyPartDirection[0] = { -1.f, 0.f };
			directionCache.pop();
			break;
		}
	}
}

void Player::updatePartDirection()
{
	if (static_cast<int>(body[0].getPosition().x) % 20 == 0 && static_cast<int>(body[0].getPosition().y) % 20 == 0) 
	{
		for (int i = body.size() - 1; i > 0; i--)
		{
			if (bodyPartDirection[i] != bodyPartDirection[i - 1])
			{
				if (((body[i - 1].getPosition().x - body[i].getPosition().x) == bodyPartDirection[i - 1][0] * 20) && ((body[i - 1].getPosition().y - body[i].getPosition().y) == bodyPartDirection[i - 1][1] * 20))
				{
					bodyPartDirection[i] = bodyPartDirection[i - 1];
				}
			}
		}
	}
}

void Player::updateLength()
{
	this->length++;
	growPart();
}


void Player::playerMove()
{
	for (int i = 0; i < body.size(); i++)
	{
		bodyMove(i, this->bodyPartDirection[i]);
	}
}

void Player::bodyMove(int i, std::vector<float> direction)
{
	body[i].move(direction[0] * this->moveSpeed, direction[1] * this->moveSpeed);
}

bool Player::touchingWindowBorder(sf::VideoMode videoMode, float uiHeight)
{
	if (body[0].getPosition().x > videoMode.width - 20.f)
	{
		return true;
	}
	else if (body[0].getPosition().y > videoMode.height - 20.f)
	{
		return true;
	}
	else if (body[0].getPosition().x < 0)
	{
		return true;
	}
	else if (body[0].getPosition().y < uiHeight)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::checkBodyCollision()
{
	std::vector<std::vector<int>> x = getPartPositions(80);
	for (int i = 2; i < x.size(); i++)
	{
		if ((x[0][0] == x[i][0]) && (x[0][1] == x[i][1]))
		{
			return true;
		}
	}
	return false;
}

void Player::wrapping(sf::VideoMode videoMode, float uiHeight)
{
	for (auto& part : body)
	{
		if (part.getPosition().x >= videoMode.width)
		{
			part.setPosition(0.f, part.getPosition().y);
		}
		if (part.getPosition().x < 0.f)
		{
			part.setPosition(videoMode.width, part.getPosition().y);
		}
		if (part.getPosition().y >= videoMode.height)
		{
			part.setPosition(part.getPosition().x, 0.f);
		}
		if (part.getPosition().y < uiHeight)
		{
			part.setPosition(part.getPosition().x, videoMode.height);
		}
	}
}

void Player::render(sf::RenderTarget& target)
{
	for (auto& p : this->body)
	{
		target.draw(p);
	}
}
