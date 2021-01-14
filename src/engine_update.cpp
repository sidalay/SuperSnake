#include "engine.hpp"

void Engine::Update()
{
	// Update Snake Positions
	if (TimeSinceLastMove.asSeconds() >= sf::seconds(1.f / float(Speed)).asSeconds())
	{
		sf::Vector2f ThisSectionPosition = Snake[0].GetPosition();
		sf::Vector2f LastSectionPosition = ThisSectionPosition;

		// Is there anything in the input queue?
		if (!DirectionQueue.empty())
		{
			// Make sure we do not reverse directions
			switch (SnakeDirection)
			{
				case Direction::UP:
					if (DirectionQueue.front() != Direction::DOWN)
					{
						SnakeDirection = DirectionQueue.front();
					}
					break;
				case Direction::DOWN:
					if (DirectionQueue.front() != Direction::UP)
					{
						SnakeDirection = DirectionQueue.front();
					}
					break;
				case Direction::LEFT:
					if (DirectionQueue.front() != Direction::RIGHT)
					{
						SnakeDirection = DirectionQueue.front();
					}
					break;
				case Direction::RIGHT:
					if (DirectionQueue.front() != Direction::LEFT)
					{
						SnakeDirection = DirectionQueue.front();
					}
					break;
			}
			DirectionQueue.pop_front();
		}

		// Update Score
		Score += Snake.size() + (ApplesEatenTotal + 1);
		ScoreText.setString("Score: " + std::to_string(Score));
		sf::FloatRect ScoreTextBounds = ScoreText.getGlobalBounds();
		ScoreText.setPosition(sf::Vector2f(Resolution.x - ScoreTextBounds.width - 15, -8));

		// Do we need to grow the Snake?
		if (SectionsToAdd)
		{
			AddSnakeSection();
			SectionsToAdd--;
		}

		// Update the snake's head position
		switch (SnakeDirection)
		{
			case Direction::UP:
				Snake[0].SetPosition(sf::Vector2f(ThisSectionPosition.x, ThisSectionPosition.y - 20));
				Snake[0].GetSnakeSprite().setRotation(270.f);
				break;
			case Direction::DOWN:
				Snake[0].SetPosition(sf::Vector2f(ThisSectionPosition.x, ThisSectionPosition.y + 20));
				Snake[0].GetSnakeSprite().setRotation(90.f);
				break;
			case Direction::LEFT:
				Snake[0].SetPosition(sf::Vector2f(ThisSectionPosition.x - 20, ThisSectionPosition.y));
				Snake[0].GetSnakeSprite().setRotation(180.f);
				break;
			case Direction::RIGHT:
				Snake[0].SetPosition(sf::Vector2f(ThisSectionPosition.x + 20, ThisSectionPosition.y));
				Snake[0].GetSnakeSprite().setRotation(0.f);
				break;
		}


		// Update the snake tail positions
		for (int s = 1; s < Snake.size(); s++)
		{
			ThisSectionPosition = Snake[s].GetPosition();
			Snake[s].SetPosition(LastSectionPosition);
			LastSectionPosition = ThisSectionPosition;

			// Get the previous Snake section orientation and set it for the current snake section
//			Snake[s].GetSnakeSprite().setRotation(Snake[s-1].GetSnakeSprite().getRotation());
		}

		// Rotate the snake body and tail pieces
		static int NodeCounter{1};
		if (Snake[NodeCounter].GetSnakeSprite().getRotation() != GetDirectionAngle())
		{
			Snake[NodeCounter].GetSnakeSprite().setRotation(GetDirectionAngle());
			++NodeCounter;
			if (NodeCounter > Snake.size())
			{
				NodeCounter = 1;
			}
		}

		// Run Snake section update functions
		for (auto& s:Snake)
		{
			s.Update();
		}


		// Collision detection - AppleInstance
		if (Snake[0].GetShape().getGlobalBounds().intersects(AppleInstance.GetSprite().getGlobalBounds()))
		{
			// We hit the AppleInstance, add more sections to the Snake, increase speed and move the apple
			ApplesEatenThisLevel += 1;
			ApplesEatenTotal += 1;
			ApplesEatenText.setString("Apples " + std::to_string(ApplesEatenTotal));
			sf::FloatRect CurrentLevelTextBounds = CurrentLevelText.getGlobalBounds();
			ApplesEatenText.setPosition(sf::Vector2f(CurrentLevelTextBounds.left + CurrentLevelTextBounds.width + 20, -8));

			bool BeginningNewLevel = false;

			if (ApplesEatenThisLevel >= 10)
			{
				// Begin the next level if there are more,
				// Otherwise, just stay on the last level and keep getting harder until we die
				if (CurrentLevel < MaxLevels)
				{
					BeginningNewLevel = true;
					BeginNextLevel();
				}
			}
			if (!BeginningNewLevel)
			{
				SectionsToAdd += 4;
				Speed++;
				MoveApple();
			}


		}

		// Collision detection - Snake body
		for (int s = 1; s < Snake.size(); s++)
		{
			if (Snake[0].GetShape().getGlobalBounds().intersects(Snake[s].GetShape().getGlobalBounds()))
			{
				// Game Over
				CurrentGameState = GameState::GAMEOVER;
			}
		}

		// Collision detection - Wall
		for (auto& w:WallSections)
		{
			if (Snake[0].GetShape().getGlobalBounds().intersects(w.GetShape().getGlobalBounds()))
			{
				// Game Over
				CurrentGameState = GameState::GAMEOVER;
			}
		}

		// Reset the last move timer
		TimeSinceLastMove = sf::Time::Zero;

	} // END update snake position
}