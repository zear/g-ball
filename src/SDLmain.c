#include "SDLmain.h"
#include <SDL.h>
#include "global.h"

SDL_Surface *screen = NULL;

int initSDL()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK))
	{
		fprintf(stderr, "ERROR (initSDL): Failed to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	SDL_JoystickOpen(0);

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	SDL_ShowCursor(SDL_DISABLE);

	return 0;
}

void cleanSDL()
{
	SDL_Quit();
}
