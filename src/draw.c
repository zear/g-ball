#include "draw.h"
#include "baseent.h"
#include "input.h"
#include "font.h"
#include "logic.h"
#include "SDLgfx.h"
#include "SDLmain.h"

void drawMenu()
{
	drawBackground(8, 56, 8);
	drawText("G-Ball", 120, 100, &FontLarge);
	drawText("a g-sensor ball game", 100, 120, &FontSmall);
}

void drawInGame()
{
	char joyInfo[10]; // temporary

	drawBackground(0, 0, 0);	
	drawMap();
	drawEntities();

	//sprintf(joyInfo, "x:%d\ny:%d\n", SDL_JoystickGetAxis(joy, 0), SDL_JoystickGetAxis(joy, 1));
	//drawText(joyInfo, 250, 200, &FontSmall);
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

		default:
			break;
	}

	updateScreen();
}
