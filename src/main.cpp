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

	chipotto::Emulator emulator;

	if (emulator.IsValid())
	{
		chipotto::Gamefile* gamefile;
		chipotto::Loader::ReadFromFile("resources\\TICTAC", &gamefile);

		emulator.Load(gamefile);

		if (!gamefile->isValid())
		{
			delete gamefile;
			goto quit;
		}

		while (true)
		{
			if (!emulator.Tick())
			{
				break;
			}
		}
	}

quit:
	SDL_Quit();
	return 0;
}