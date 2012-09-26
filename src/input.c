#include "input.h"
#include <SDL.h>
#include "logic.h"

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
		}
	}
}
