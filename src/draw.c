#include "draw.h"
#include "baseent.h"
#include "font.h"
#include "input.h"
#include "logic.h"
#include "menu.h"
#include "SDLgfx.h"
#include "SDLmain.h"

void drawMenu()
{
	drawBackground(8, 56, 8);
	drawText("G-Ball", 130, 20, &FontLarge);
	drawText("a g-sensor ball game", 110, 40, &FontSmall);

	menuDraw(CurrentMenu, 0, 140, 100);
	menuDraw(CurrentMenu, 1, 140, 110);
	menuDraw(CurrentMenu, 2, 140, 120);
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
