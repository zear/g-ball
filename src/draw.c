#include "draw.h"
#include "font.h"
#include "logic.h"
#include "SDLgfx.h"

void drawMenu()
{
	drawBackground(8, 56, 8);
	drawText("G-Ball", 120, 100, &FontLarge);
	drawText("a g-sensor ball game", 100, 120, &FontSmall);
}

void drawInGame()
{
	drawBackground(0, 0, 0);
	
	drawEntities();
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
