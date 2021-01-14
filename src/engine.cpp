#include "../headers/engine.hpp"

const sf::Time Engine::TimePerFrame = sf::seconds(1.f/60.f);

Engine::Engine()
{
	Resolution = sf::Vector2f(800, 600);
	Window.create(sf::VideoMode(Resolution.x, Resolution.y), "Super Snake ++", sf::Style::Default);
	Window.setFramerateLimit(FPS);
	MaxLevels = 0;
	CheckLevelFiles();

	StartGame();

	MainFont.loadFromFile("assets/fonts/slant_regular.ttf");          // Load in the text from assets/fonts

	// TITLE BAR TITLE TEXT
	SetupText(&TitleText, MainFont, "SUPER SNAKE++", 27, sf::Color::Cyan);
	TitleText.setOutlineColor(sf::Color::Black);
	TitleText.setOutlineThickness(2);
	sf::FloatRect TitleTextBounds = TitleText.getLocalBounds();
	TitleText.setPosition(sf::Vector2f(Resolution.x / 2 - TitleTextBounds.width / 2, -8));

	// TITLE BAR CURRENT LEVEL TEXT
	SetupText(&CurrentLevelText, MainFont, "Level 1", 27, sf::Color::Cyan);
	CurrentLevelText.setOutlineColor(sf::Color::Black);
	CurrentLevelText.setOutlineThickness(2);
	CurrentLevelText.setPosition(sf::Vector2f(15, -8));
	sf::FloatRect CurrentLevelTextBounds = CurrentLevelText.getGlobalBounds();

	// TITLE BAR TOTAL APPLES EATEN TEXT
	SetupText(&ApplesEatenText, MainFont, "Apples 0", 27, sf::Color::Cyan);
	ApplesEatenText.setOutlineColor(sf::Color::Black);
	ApplesEatenText.setOutlineThickness(2);
	ApplesEatenText.setPosition(sf::Vector2f(CurrentLevelTextBounds.left + CurrentLevelTextBounds.width + 20, -8));

	// TITLE BAR SCORE TEXT
	SetupText(&ScoreText, MainFont, "Score: " + std::to_string(Score), 27, sf::Color::Cyan);
	ScoreText.setOutlineColor(sf::Color::Black);
	ScoreText.setOutlineThickness(2);
	sf::FloatRect ScoreTextBounds = ScoreText.getGlobalBounds();
	ScoreText.setPosition(sf::Vector2f(Resolution.x - ScoreTextBounds.width - 15, -8));

	// BOTTOM BAR KEYBINDS TEXT
	SetupText(&KeyBindsText, MainFont, "esc: menu  /   spacebar: pause   /   vol up: k   vol down: j", 20, sf::Color::Cyan);
	KeyBindsText.setOutlineColor(sf::Color::Black);
	KeyBindsText.setOutlineThickness(2);
	sf::FloatRect  KeyBindsTextBounds = KeyBindsText.getLocalBounds();
	KeyBindsText.setPosition(sf::Vector2f(20,575));

	// GAME OVER TEXT
	SetupText(&GameOverText, MainFont, "GAME OVER", 72, sf::Color::Yellow);
	sf::FloatRect GameOverTextBounds = GameOverText.getLocalBounds();
	GameOverText.setPosition(sf::Vector2f(Resolution.x / 2 - GameOverTextBounds.width / 2, 100));
	GameOverText.setOutlineColor(sf::Color::Black);
	GameOverText.setOutlineThickness(2);

	// PRESS ENTER TO CONTINUE TEXT
	SetupText(&PressEnterText, MainFont, "Press ENTER to start over", 38, sf::Color::Green);
	sf::FloatRect PressEnterTextBounds = PressEnterText.getLocalBounds();
	PressEnterText.setPosition(sf::Vector2f(Resolution.x / 2 - PressEnterTextBounds.width / 2, 200));
	PressEnterText.setOutlineColor(sf::Color::Black);
	PressEnterText.setOutlineThickness(2);

	// PAUSE MENU TEXT
	SetupText(&PauseText, MainFont, "PAUSED", 72, sf::Color::Yellow);
	sf::FloatRect PauseTextBounds = PauseText.getLocalBounds();
	PauseText.setPosition(sf::Vector2f(Resolution.x / 2 - PauseTextBounds.width / 2, 200));
	PauseText.setOutlineColor(sf::Color::Black);
	PauseText.setOutlineThickness(2);
}

void Engine::StartGame()
{
	Score = 0;
	Speed = 2;
	SnakeDirection = Direction::RIGHT;
	TimeSinceLastMove = sf::Time::Zero;
	SectionsToAdd = 0;
	DirectionQueue.clear();
	WallSections.clear();
	ApplesEatenThisLevel = 0;
	ApplesEatenTotal = 0;
	CurrentLevel = 1;
	LoadBackgroundTexture();
	LoadWindowFrame();
	LoadLevel(CurrentLevel);
	LoadSnakeHead();
	LoadSnakeBody();
	LoadSnakeTail();
	LoadSnakeTurn();
	NewSnake();
	MoveApple();
	CurrentGameState = GameState::RUNNING;
	LastGameState = CurrentGameState;
	CurrentLevelText.setString("Level " + std::to_string(CurrentLevel));
	ApplesEatenText.setString("Apples " + std::to_string(ApplesEatenTotal));
	sf::FloatRect CurrentLevelTextBounds = CurrentLevelText.getGlobalBounds();
	ApplesEatenText.setPosition(sf::Vector2f(CurrentLevelTextBounds.left + CurrentLevelTextBounds.width + 20, -8));
	ScoreText.setString("Score: " + std::to_string(Score));
	sf::FloatRect ScoreTextBounds = ScoreText.getGlobalBounds();
	ScoreText.setPosition(sf::Vector2f(Resolution.x - ScoreTextBounds.width - 15, -8));
}

/*
 * Increment the level number, load the next level and reset the snake
 */
void Engine::BeginNextLevel()
{
	CurrentLevel += 1;
	WallSections.clear();
	DirectionQueue.clear();
	Speed = 2 + CurrentLevel;
	SnakeDirection = Direction::RIGHT;
	SectionsToAdd = 0;
	ApplesEatenThisLevel = 0;

	LoadLevel(CurrentLevel);
	NewSnake();
	MoveApple();

	CurrentLevelText.setString("Level " + std::to_string(CurrentLevel));
	sf::FloatRect CurrentLevelTextBounds = CurrentLevelText.getGlobalBounds();
	ApplesEatenText.setPosition(sf::Vector2f(CurrentLevelTextBounds.left + CurrentLevelTextBounds.width + 20, -8));
}

// This is the initial snake created at the start of each level
void Engine::NewSnake()
{
	Snake.clear();
	Snake.emplace_back(sf::Vector2f(StartPosX,StartPosY), SnakeHeadTexture, GetDirectionAngle());
	Snake.emplace_back(sf::Vector2f(StartPosX - 20,StartPosY), SnakeBodyTexture, GetDirectionAngle());
	Snake.emplace_back(sf::Vector2f(StartPosX - 40,StartPosY), SnakeTailTexture, GetDirectionAngle());
}

// Just add the section at the same position as the last section of the snake, it will follow normally.
void Engine::AddSnakeSection()
{
	sf::Vector2f NewSectionPosition = Snake[Snake.size() - 2].GetPosition();

	Snake.insert(Snake.end() - 1, {NewSectionPosition, SnakeBodyTexture, GetDirectionAngle()});
}

void Engine::MoveApple()
{
	// Find a location to place the apple
	// Must not be inside the snake, or a wall

	// Divide the field into sections the size of the apple - remove 2 to exclude the exterior walls
	sf::Vector2f AppleResolution = sf::Vector2f((Resolution.x / 20) - 2, (Resolution.y / 20) - 2);
	sf::Vector2f NewAppleLocation;
	bool BadLocation = false;
	std::srand(time(nullptr));
	// Loop until we find a valid location
	do
	{
		BadLocation = false;
		// Generate a random location
		NewAppleLocation.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)AppleResolution.x)) * 20;
		NewAppleLocation.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)AppleResolution.y)) * 20;

		// Check if it is in the Snake
		for (auto& s:Snake)
		{
			if (s.GetShape().getGlobalBounds().intersects(sf::Rect<float>(NewAppleLocation.x, NewAppleLocation.y, 20, 20)))
			{
				BadLocation = true;
				break;
			}
		}

		// Check if it is in the walls
		for (auto& w:WallSections)
		{
			if (w.GetShape().getGlobalBounds().intersects(sf::Rect<float>(NewAppleLocation.x, NewAppleLocation.y, 20, 20)))
			{
				BadLocation = true;
				break;
			}
		}
	}
	while (BadLocation);

	AppleInstance.SetPosition(NewAppleLocation);
}

void Engine::TogglePause()
{
	if (CurrentGameState == GameState::RUNNING)
	{
		LastGameState = CurrentGameState;
		CurrentGameState = GameState::PAUSED;
		MainAudio.pause();
	}
	else if (CurrentGameState == GameState::PAUSED)
	{
		CurrentGameState = LastGameState;
		MainAudio.play();
	}
}

// Used to check the orientation of previous Snake to spawn proper sprite orientation for current Snake
float Engine::GetDirectionAngle() const
{
	float SnakeOrientationAngle{};
	switch (SnakeDirection)
	{
		case Direction::UP:
			SnakeOrientationAngle = 270.0;
			break;
		case Direction::DOWN:
			SnakeOrientationAngle = 90.0;
			break;
		case Direction::LEFT:
			SnakeOrientationAngle = 180.0;
			break;
		case Direction::RIGHT:
			SnakeOrientationAngle = 0.0;
			break;
	}
	return SnakeOrientationAngle;
}

void Engine::Run()
{
	sf::Clock Clock;

	CheckAudio();
	MainAudio.setVolume(50);
	MainAudio.play();
	MainAudio.setLoop(true);

	// Main loop - runs until the window is closed
	while (Window.isOpen())
	{
		sf::Time DeltaTime = Clock.restart();

		if (CurrentGameState == GameState::PAUSED || CurrentGameState == GameState::GAMEOVER)
		{
			// If we are paused, then check for input (so we can un-pause), then just continue to the next loop
			Input();

			// Draw the game over screen
			if (CurrentGameState == GameState::GAMEOVER)
			{
				Draw();
			}

			sf::sleep(sf::milliseconds(2)); // Sleep so we don't peg the CPU
			continue;
		}

		TimeSinceLastMove += DeltaTime;

		sf::err().rdbuf(nullptr);
		Input();
		Update();
		Draw();
	}
}