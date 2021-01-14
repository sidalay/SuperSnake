#include "engine.hpp"

/*
 * Check the levels manifest file and make sure that we can open each level file.
 * Add good level file names to the 'levels' vector and increment the MaxLevels.
 */
void Engine::CheckLevelFiles()
{
	// Load the levels manifest file
	std::ifstream LevelsManifest ("assets/levels/levels.txt");
	std::ifstream TestFile;
	for (std::string ManifestLine; std::getline(LevelsManifest, ManifestLine);)
	{
		// Check that we can open the level file
		TestFile.open("assets/levels/" + ManifestLine);
		if (TestFile.is_open())
		{
			// The level file opens, lets add it to the list of available levels
			Levels.emplace_back("assets/levels/" + ManifestLine);
			TestFile.close();
			MaxLevels ++;
		}
	}
}

/*
 * Load a level from a file and check for 'x' characters to add wall sections
 * @param LevelNumber int - the number of the level to load
 */
void Engine::LoadLevel(int LevelNumber)
{
	std::string LevelFile = Levels[LevelNumber - 1];
	std::ifstream Level (LevelFile);
	std::string Line;
	if (Level.is_open())
	{
		for (int y = 0; y < 30; y++)
		{
			std::getline(Level, Line);
			for (int x = 0; x <40; x++)
			{
				if (Line[x] == 'x')
				{
					WallSections.emplace_back(Wall(sf::Vector2f(x * 20, y * 20), sf::Vector2f(30, 30)));
				}
			}
		}
	}
	Level.close();
}