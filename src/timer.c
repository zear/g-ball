#include "timer.h"
#include <SDL.h>
#include "global.h"

int frameRate = 0;

int calculateFrameRate()
{
	static int currentTime = 0; //SDL_GetTicks();
	static double accumulator = 0;
	static double frameTime = 1000.0/(double)FPS;
	int newTime;
	int deltaTime;
	int sleep = 1;

	newTime = SDL_GetTicks();
	deltaTime = newTime - currentTime;
	currentTime = newTime;
#if defined(NO_FPS_LIMIT)
	accumulator = frameTime;
#else
	accumulator += deltaTime;
#endif

	while(accumulator >= frameTime)
	{
		frameRate = 1000/accumulator; // NOTE: This counts how many frames at the current frame draw time would be possible to draw in 1000ms (1s). It is not actual FPS.
#if !defined(NO_FPS_LIMIT)
		if(frameRate > 60)
		{
			frameRate = 60;
		}
#endif
		accumulator -= frameTime;
		sleep = 0;
	}

	return sleep;
}
