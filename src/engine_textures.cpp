#include "engine.hpp"

int Engine::LoadWindowFrame()
{
	if (!WindowFrame.loadFromFile("assets/image/snakeframe.png"))
	{
		return EXIT_FAILURE;
	}
	MainWindowFrame = (sf::Sprite)WindowFrame;
	return 0;
}

int Engine::LoadBackgroundTexture()
{
	if (!BackgroundTexture.loadFromFile("assets/image/snakebackground.png"))
	{
		return EXIT_FAILURE;
	}
	BackgroundSprite = (sf::Sprite)BackgroundTexture;
	return 0;
}

int Engine::LoadSnakeHead()
{
	if (!SnakeHeadTexture.loadFromFile("assets/image/snakehead.png"))
	{
		return EXIT_FAILURE;
	}
	return 0;
}

int Engine::LoadSnakeBody()
{
	if (!SnakeBodyTexture.loadFromFile("assets/image/snakebody.png"))
	{
		return EXIT_FAILURE;
	}
	return 0;
}

int Engine::LoadSnakeTail()
{
	if (!SnakeTailTexture.loadFromFile("assets/image/snaketail.png"))
	{
		return EXIT_FAILURE;
	}
	return 0;
}

int Engine::LoadSnakeTurn()
{
	if (!SnakeTurnTexture.loadFromFile("assets/image/snakebodyturn.png"))
	{
		return EXIT_FAILURE;
	}
	return 0;
}