#include "engine.hpp"

int Engine::CheckAudio()
{
	if (!MainAudio.openFromFile("assets/music/snakebeat.flac"))
	{
		return EXIT_FAILURE;
	}
	return 0;
}

void Engine::LowerVolume()
{
	if (VolumeLevel > 0.f)
	{
		VolumeLevel -= 5;
	}
	MainAudio.setVolume(VolumeLevel);
}

void Engine::RaiseVolume()
{
	if (VolumeLevel < 100.f)
	{
		VolumeLevel += 5;
	}
	MainAudio.setVolume(VolumeLevel);
}

//void Engine::MuteVolume()
//{
//
//}