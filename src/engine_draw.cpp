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

	// Draw Text
//	Window.draw(BackgroundSprite);
	Window.draw(MainWindowFrame);
	Window.draw(TitleText);
	Window.draw(CurrentLevelText);
	Window.draw(ApplesEatenText);
	Window.draw(ScoreText);
	Window.draw(KeyBindsText);

	// Draw AppleInstance
//	Window.draw(AppleInstance.GetSprite());
	Window.draw(AppleInstance.GetAppleSprite());

	// Draw Snake sections
	for (auto& s:Snake)
	{
//		Window.draw(s.GetShape());
		Window.draw(s.GetSnakeSprite());
	}


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
