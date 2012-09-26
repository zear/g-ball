#include "draw.h"
#include "logic.h"
#include "SDLgfx.h"

void drawMenu()
{
}

void drawInGame()
{
}

void draw()
{
	switch(GameState)
	{
		case STATE_MENU:
			drawMenu();
			break;
		case STATE_INGAME:
			drawInGame();
			break;
	}

	updateScreen();
}
