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

	setGameState(STATE_INIT);

	while(!quit)
	{
		doFrame();
		{
			input();
			logic();
			draw();
		}
	}

	clean();

	return 0;
}
