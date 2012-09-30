#include "input.h"
#include <SDL.h>
#include "logic.h"

_Bool keystate[2048];
struct JoystateStruct Joystate;

SDL_Event event;

void input()
{
	if(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				setGameState(STATE_EXIT);
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				keystate[event.key.keysym.sym] = (event.type == SDL_KEYDOWN);
				break;
			case SDL_JOYAXISMOTION:
				switch(event.jaxis.axis)
				{
					case 0:
						Joystate.x = event.jaxis.value;
						break;
					case 1:
						Joystate.y = event.jaxis.value;
						break;
				}
				break;
		}
	}
}
