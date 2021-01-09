#include "apple.hpp"

Apple::Apple()
{
	sf::Vector2f StartingPosition(StartPosX, StartPosY);
	Sprite.setSize(sf::Vector2f(AppleSizeX, AppleSizeY));
	Sprite.setFillColor(sf::Color::Red);
	Sprite.setPosition(StartingPosition);
}

void Apple::SetPosition(sf::Vector2f NewPosition)
{
	Sprite.setPosition(NewPosition);
}

sf::RectangleShape Apple::GetSprite()
{
	return Sprite;
}