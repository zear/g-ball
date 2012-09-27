#include "draw.h"
#include "input.h"
#include "logic.h"
#include "SDLmain.h"
#include "timer.h"
#include "baseent.h"

int main()
{
	quit = 0;

	initEntities();
	initSDL();

	setGameState(STATE_MENU);

	while(!quit)
	{
		if(calculateFrameRate())
		{
			SDL_Delay(1);
		}
		else
		{
			input();
			logic();
			draw();
		}
	}

	clean();

	return 0;
}
