#ifndef SNAKE_WALL_HPP
#define SNAKE_WALL_HPP

#include <SFML/Graphics.hpp>

class Wall
{
private:
	sf::RectangleShape WallShape;

public:
	Wall(sf::Vector2f Position, sf::Vector2f Size);

	sf::RectangleShape GetShape();
};


#endif //SNAKE_WALL_HPP
