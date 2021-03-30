#include "snakesection.hpp"

SnakeSection::SnakeSection(sf::Vector2f StartPosition, const sf::Texture& SnakeSkinTexture, float SnakeDirection)
		: SnakeSkinSprite{SnakeSkinTexture}
{
	Section.setSize(sf::Vector2f(SnakeRectangleSizeX,SnakeRectangleSizeY));
//	Section.setFillColor(sf::Color::Green);
//	Section.setOutlineColor(sf::Color::Black);
//	Section.setOutlineThickness(1);
	Section.setPosition(StartPosition);
	Position = StartPosition;
	SnakeSkinSprite.setPosition(Position);
	SnakeSkinSprite.setOrigin(10,10);
	SnakeSkinSprite.setRotation(SnakeDirection);
}

sf::Vector2f SnakeSection::GetPosition()
{
	return Position;
}

void SnakeSection::SetPosition(sf::Vector2f NewPosition)
{
	Position = NewPosition;
}

sf::RectangleShape SnakeSection::GetShape()
{
	return Section;
}

void SnakeSection::Update()
{
	Section.setPosition(Position);
	SnakeSkinSprite.setPosition(Position);
}

sf::Sprite& SnakeSection::GetSnakeSprite()
{
	return SnakeSkinSprite;
}