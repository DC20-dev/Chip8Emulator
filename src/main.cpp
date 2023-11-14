#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "emulator.h"
#include "sdl/loader.h"

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return -1;
	}
	float last_tick = SDL_GetTicks64();

	chipotto::Emulator emulator;

	if (!emulator.IsValid())
	{
		goto quit_on_error;	// escaping sequence
	}

	chipotto::Gamefile* gamefile;
	if (!chipotto::Loader::ReadFromFile("resources\\TICTAC", &gamefile))
	{
		goto quit_on_error;	// same
	}

	emulator.Load(gamefile);


	while (true)
	{
		float deltatime = last_tick - SDL_GetTicks64();
		deltatime *= 0.001f;
		last_tick = deltatime;

		if (!emulator.Tick(deltatime))
		{
			break;
		}
	}

cleanup:				// jump here if quitting with cleanup is needed
		delete gamefile;

quit:
	SDL_Quit();
	return 0;

quit_on_error:
	SDL_Quit();
	return -1;
}