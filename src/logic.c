#include "logic.h"
#include "font.h"
#include "SDLmain.h"

enum GameStateType GameState = STATE_INIT;
enum GameStateType NewGameState;
int quit;

void setGameState(enum GameStateType NewState)
{
	NewGameState = NewState;
}

void changeGameState()
{
	// unload current
	switch(GameState)
	{
		case STATE_MENU:
			break;
		case STATE_INGAME:
			break;

		default:
			break;
	}

	// load new
	switch(NewGameState)
	{
		case STATE_MENU:
			break;
		case STATE_INGAME:
			break;

		default:
			break;
	}

	GameState = NewGameState;
}

void logicInit()
{
	// init all game assets that we keep through the entire run time
	loadFont(&FontSmall, "./data/gfx/fontSmall.bmp", 5, 9);
	loadFont(&FontLarge, "./data/gfx/fontLarge.bmp", 10, 18);
	setGameState(STATE_MENU);
}

void logicMenu()
{
	int leaving = 0;

	if(leaving)
	{
		setGameState(STATE_EXIT);
	}
}

void logicInGame()
{
	int leaving = 0;

	if(leaving)
	{
		setGameState(STATE_MENU);
	}
}

void logic()
{
	if(NewGameState != GameState)
	{
		changeGameState();
	}

	switch(GameState)
	{
		case STATE_EXIT:
			quit = 1;
			break;
		case STATE_INIT:
			logicInit();
			break;
		case STATE_MENU:
			logicMenu();
			break;
		case STATE_INGAME:
			logicInGame();
			break;

		default:
		break;
	}
}

void clean()
{
	cleanSDL();
}
