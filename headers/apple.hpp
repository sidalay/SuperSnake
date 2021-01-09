#ifndef SNAKE_APPLE_HPP
#define SNAKE_APPLE_HPP

#include <SFML/Graphics.hpp>

class Apple
{
private:
	sf::RectangleShape Sprite;
	int StartPosX{600};
	int StartPosY{200};
	int AppleSizeX{18};
	int AppleSizeY{18};

public:
	Apple();

	void SetPosition(sf::Vector2f NewPosition);
	sf::RectangleShape GetSprite();
};


#endif //SNAKE_APPLE_HPP
