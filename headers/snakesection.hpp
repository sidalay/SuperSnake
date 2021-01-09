#ifndef SNAKE_SNAKESECTION_HPP
#define SNAKE_SNAKESECTION_HPP

#include <SFML/Graphics.hpp>


class SnakeSection
{
private:
	sf::Vector2f Position;
	sf::RectangleShape Section;
	int SnakeRectangleSizeX{20};
	int SnakeRectangleSizeY{20};

public:
	explicit SnakeSection(sf::Vector2f StartPosition);

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f NewPosition);

	sf::RectangleShape GetShape();

	void Update();
};


#endif //SNAKE_SNAKESECTION_HPP
