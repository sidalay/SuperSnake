#include "wall.hpp"

Wall::Wall(sf::Vector2f Position, sf::Vector2f Size)
{
	WallShape.setSize(Size);
	WallShape.setFillColor(sf::Color::White);
	WallShape.setPosition(Position);
}

sf::RectangleShape Wall::GetShape()
{
	return WallShape;
}