#include "draw.h"
#include "logic.h"
#include "SDLgfx.h"
#include "baseent.h"

Entity *ent = NULL;

void drawMenu()
{
	if (!ent)
		ent = baseent_super(NULL);
	
	ent->draw(ent);
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
