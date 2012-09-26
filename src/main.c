#include "draw.h"
#include "input.h"
#include "logic.h"
#include "SDLmain.h"
#include "timer.h"

int main()
{
	quit = 0;

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
