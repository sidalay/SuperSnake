#ifndef SNAKE_APPLE_HPP
#define SNAKE_APPLE_HPP

#include <SFML/Graphics.hpp>

class Apple
{
private:
	sf::RectangleShape Sprite;
	sf::Texture ApplePNG;
	sf::Sprite AppleSprite;
	int StartPosX{600};
	int StartPosY{200};
	int AppleSizeX{20};
	int AppleSizeY{20};

public:
	Apple();

	void SetPosition(sf::Vector2f NewPosition);
	int LoadAppleTexture();
	sf::Sprite GetAppleSprite();
	sf::RectangleShape GetSprite();
};


#endif //SNAKE_APPLE_HPP
