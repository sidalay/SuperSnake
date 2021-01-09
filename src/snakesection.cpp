#include "snakesection.hpp"

SnakeSection::SnakeSection(sf::Vector2f StartPosition)
{
	Section.setSize(sf::Vector2f(SnakeRectangleSizeX,SnakeRectangleSizeY));
	Section.setFillColor(sf::Color::Green);
	Section.setPosition(StartPosition);
	Position = StartPosition;
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
}