#ifndef SNAKE_ENGINE_HPP
#define SNAKE_ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <deque>
#include <fstream>
#include <string>
#include "snakesection.hpp"
#include "apple.hpp"
#include "wall.hpp"

class Engine {

private:
	// Create window
	sf::Vector2f Resolution;
	sf::RenderWindow Window;
	const unsigned int FPS{60};
	static const sf::Time TimePerFrame;

	// Main Window Frame
	sf::Texture WindowFrame;
	sf::Sprite MainWindowFrame;

	// Background Image
	sf::Texture BackgroundTexture;
	sf::Sprite BackgroundSprite;

	// Snake Texture Loading
	sf::Texture SnakeHeadTexture;
	sf::Texture SnakeBodyTexture;
	sf::Texture SnakeTailTexture;
	sf::Texture SnakeTurnTexture;

	std::vector<SnakeSection> Snake;

	int SnakeDirection{};
	std::deque<int> DirectionQueue;     // Queue for direction key presses

	int Speed{};
	int StartPosX{400};                 // Snake head starting position X
	int StartPosY{280};                 // Snake head starting position y

	int SectionsToAdd{};                // How many sections to add to the snake

	Apple AppleInstance;
	int ApplesEatenThisLevel{};
	int ApplesEatenTotal{};
	unsigned long long int Score{};

	std::vector<Wall> WallSections;
	int CurrentLevel{};
	int MaxLevels{};
	std::vector<std::string> Levels;

	// TEXT VARIABLES
	sf::Font MainFont;
	sf::Text TitleText;
	sf::Text ApplesEatenText;
	sf::Text CurrentLevelText;
	sf::Text ScoreText;
	sf::Text GameOverText;
	sf::Text PressEnterText;
	sf::Text PauseText;
	sf::Text KeyBindsText;

	// MUSIC VARIABLES
	sf::Music MainAudio;
	float VolumeLevel{35};

	sf::Time TimeSinceLastMove;

	int CurrentGameState{};
	int LastGameState{};                // For Storing the last state the game was in when pausing.

public:
	enum Direction {UP,RIGHT,DOWN,LEFT};
	enum GameState {RUNNING,PAUSED,GAMEOVER};

	// Constructor
	Engine();


	// Start the Game
	void StartGame();

	// Start Next Level
	void BeginNextLevel();

	// Draw to screen
	void Draw();

	// Update screen
	void Update();

	// Input Controls
	void Input();           // Create events (for ex. closing window)
	void AddDirection(int);
	float GetDirectionAngle() const;
	void TogglePause();

	void NewSnake();        // Create the initial snake at start of game
	void AddSnakeSection(); // Add a new section to the snake

	// Move apple function
	void MoveApple();

	// Audio Controls
	int CheckAudio();
	void LowerVolume();
	void RaiseVolume();

	// Setup Text to be displayed on screen
	static void SetupText(sf::Text *TextItem, const sf::Font &Font, const sf::String &Value, int Size, sf::Color Color);
	void TitleBarText();
	void BottomBarText();
	void GameOverMessageText();
	void PauseMenuText();

	// Check all of the files to add to the levels vector
	void CheckLevelFiles();
	void LoadLevel(int LevelNumber);

	// Load Textures
	int LoadWindowFrame();
	int LoadBackgroundTexture();
	int LoadSnakeHead();
	int LoadSnakeBody();
	int LoadSnakeTail();
	int LoadSnakeTurn();

	// The main loop will be in the run function
	void Run();
};


#endif //SNAKE_ENGINE_HPP
