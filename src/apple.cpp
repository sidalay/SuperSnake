#include "apple.hpp"

Apple::Apple()
{
	sf::Vector2f StartingPosition(StartPosX, StartPosY);
	Sprite.setSize(sf::Vector2f(AppleSizeX, AppleSizeY));
//	Sprite.setFillColor(sf::Color::Red);
	Sprite.setPosition(StartingPosition);
	LoadAppleTexture();
	AppleSprite.setPosition(StartingPosition);
	AppleSprite.setOrigin(10,10);
}

void Apple::SetPosition(sf::Vector2f NewPosition)
{
	Sprite.setPosition(NewPosition);
	AppleSprite.setPosition(NewPosition);
}

sf::RectangleShape Apple::GetSprite()
{
	return Sprite;
}

int Apple::LoadAppleTexture()
{
	if (!ApplePNG.loadFromFile("assets/image/snakeapple.png"))
	{
		return EXIT_FAILURE;
	}
	AppleSprite = (sf::Sprite)ApplePNG;
	return 0;
}

sf::Sprite Apple::GetAppleSprite()
{
	return AppleSprite;
}

