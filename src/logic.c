#include "logic.h"
#include "SDLmain.h"
#include "baseent.h"

enum GameStateType GameState = STATE_MENU;
enum GameStateType NewGameState;
int quit;

Entity *ents[256];

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
	}

	// load new
	switch(NewGameState)
	{
		case STATE_MENU:
			break;
		case STATE_INGAME:
			break;
	}

	GameState = NewGameState;
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
		case STATE_MENU:
			logicMenu();
			break;
		case STATE_INGAME:
			logicInGame();
			break;
	}
}

void clean()
{
	cleanSDL();
}
