#include "engine.hpp"

void Engine::Draw()
{
	// Make sure screen is clear
	Window.clear(sf::Color::Black);

	// Draw Walls
	for (auto& w:WallSections)
	{
		Window.draw(w.GetShape());
	}

	// Draw Apple
	Window.draw(Apple.GetSprite());

	// Draw Snake sections
	for (auto& s:Snake)
	{
		Window.draw(s.GetShape());
	}

	// Draw Text
	Window.draw(TitleText);
	Window.draw(CurrentLevelText);
	Window.draw(ApplesEatenText);
	Window.draw(ScoreText);

	// Draw GameOver
	if (CurrentGameState == GameState::GAMEOVER)
	{
		Window.draw(GameOverText);
		Window.draw(PressEnterText);
	}

	// Draw Paused
	if (CurrentGameState == GameState::PAUSED)
	{
		Window.draw(PauseText);
	}

	// Display everything that has been set up previously
	Window.display();
}
