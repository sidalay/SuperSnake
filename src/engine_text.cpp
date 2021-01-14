#include "engine.hpp"

void TitleBarText()
{

}

void BottomBarText()
{

}

void GameOverMessageText()
{

}

void PauseMenuText()
{

}

void Engine::SetupText(sf::Text *TextItem, const sf::Font &Font, const sf::String &Value, int Size, sf::Color Color)
{
	TextItem->setFont(Font);
	TextItem->setString(Value);
	TextItem->setCharacterSize(Size);
	TextItem->setFillColor(Color);
}