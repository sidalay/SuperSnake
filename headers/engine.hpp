#ifndef SNAKE_ENGINE_HPP
#define SNAKE_ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
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

	std::vector<SnakeSection> Snake;

	int SnakeDirection{};
	std::deque<int> DirectionQueue;     // Queue for direction key presses

	int Speed{};
	int StartPosX{400};                 // Snake head starting position X
	int StartPosY{280};                 // Snake head starting position y

	int SectionsToAdd{};                // How many sections to add to the snake

	Apple Apple;
	int ApplesEatenThisLevel{};
	int ApplesEatenTotal{};
	unsigned long long int Score{};

	std::vector<Wall> WallSections;
	int CurrentLevel{};
	int MaxLevels{};
	std::vector<std::string> Levels;

	sf::Font MainFont;
	sf::Text TitleText;
	sf::Text ApplesEatenText;
	sf::Text CurrentLevelText;
	sf::Text ScoreText;
	sf::Text GameOverText;
	sf::Text PressEnterText;

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

	// Setup Text to be displayed on screen
	static void SetupText(sf::Text *TextItem, const sf::Font &Font, const sf::String &Value, int Size, sf::Color Color);

	// Create events (for ex. closing window)
	void Input();
	// Add a direction
	void AddDirection(int);
	// Add pausing capability
	void TogglePause();

	// Create the initial snake at start of game
	void NewSnake();
	// Add a new section to the snake
	void AddSnakeSection();

	// Move apple function
	void MoveApple();

	// Check all of the files to add to the levels vector
	void CheckLevelFiles();
	// Load the Level
	void LoadLevel(int LevelNumber);

	// The main loop will be in the run function
	void Run();
};


#endif //SNAKE_ENGINE_HPP
