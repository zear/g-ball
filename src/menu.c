#include "menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "font.h"
#include "global.h"
#include "input.h"
#include "logic.h"

MenuContainer *CurrentMenu = NULL;
MenuItem *SelectedItem = NULL;

MenuContainer *MenuMain = NULL;
MenuContainer *MenuOptions = NULL;

MenuContainer *menuCreateNew(MenuContainer *Container, int number, char *caption, MenuAction Action)
{
	MenuItem *NewItem = NULL;

	if(Container == NULL)
	{
		Container = malloc(sizeof(MenuContainer));
		if(Container == NULL)
		{
			fprintf(stderr, "ERROR: menuCreateNew: Out of memory!\n");
			return NULL;
		}
		Container->Menu = NULL;
		Container->size = 0;
	}

	NewItem = malloc(sizeof(MenuItem));
	if(NewItem == NULL)
	{
		fprintf(stderr, "ERROR: menuCreateNew: Out of memory!\n");
		return Container; // TODO: instead of returning destroy the container
	}

	NewItem->number = number;
	NewItem->Action = Action;
	strcpy(NewItem->caption, caption);

	NewItem->Next = Container->Menu;
	Container->Menu = NewItem;
	Container->size++;

	return Container;
}

MenuItem *menuSwitchItem(MenuContainer *Container, int number)
{
	MenuItem *NewItem = Container->Menu;

	while(NewItem != NULL)
	{
		if(NewItem->number == number)
		{
			return NewItem;
		}

		NewItem = NewItem->Next;
	}

	return NULL;
}

void menuAction(MenuItem *Item)
{
	switch(Item->Action)
	{
		case ACTION_NEW_GAME:
			setGameState(STATE_INGAME);
			break;
		case ACTION_OPTIONS:
			break;
		case ACTION_QUIT:
			setGameState(STATE_EXIT);
			break;

		default:
			break;
	}
}

void menuDeleteSingle(MenuContainer *Container)
{
	MenuItem *CurrentItem;

	if(Container == NULL)
	{
		return;
	}

	CurrentItem = Container->Menu;
	while(CurrentItem != NULL)
	{
		Container->Menu = CurrentItem->Next;
		free(CurrentItem);
		CurrentItem = Container->Menu;
	}
}

void menuDeleteAll()
{
	menuDeleteSingle(MenuMain);
}

void menuLoadAll()
{
	MenuMain = menuCreateNew(MenuMain, 0, "New game", ACTION_NEW_GAME);
	MenuMain = menuCreateNew(MenuMain, 1, "Options", ACTION_OPTIONS);
	MenuMain = menuCreateNew(MenuMain, 2, "Quit", ACTION_QUIT);

	CurrentMenu = MenuMain;
	SelectedItem = menuSwitchItem(CurrentMenu, 0);
}

void menuInput()
{
	MenuItem *NewItem = NULL;
	int newItemNumber = SelectedItem->number;

	if(keystate[SDLK_UP])
	{
		keystate[SDLK_UP] = 0;
		newItemNumber--;
	}
	else if(keystate[SDLK_DOWN])
	{
		keystate[SDLK_DOWN] = 0;
		newItemNumber++;
	}

	if(newItemNumber < 0)
	{
		newItemNumber = CurrentMenu->size - 1;
	}

	if(newItemNumber >= CurrentMenu->size)
	{
		newItemNumber = 0;
	}

	if(newItemNumber != SelectedItem->number)
	{
		NewItem = menuSwitchItem(CurrentMenu, newItemNumber);
		if(NewItem != NULL)
		{
			SelectedItem = NewItem;
		}
	}

	if(keystate[SDLK_RETURN])
	{
		keystate[SDLK_RETURN] = 0;
		menuAction(SelectedItem);
	}
}

void menuDraw(MenuContainer *Container, int number, int x, int y)
{
	MenuItem *CurrentItem = Container->Menu;

	if(number < 0 || number > Container->size)
	{
		fprintf(stderr, "ERROR (menuDraw): No such menu: %d\n", number);
		return;
	}

	while(CurrentItem != NULL)
	{
		if(CurrentItem->number == number)
		{
			drawText(CurrentItem->caption, x, y, &FontSmall);

			if(CurrentItem == SelectedItem)
			{
				drawText(">", 100, y, &FontSmall);
				drawText("<", SCREEN_WIDTH - 100, y, &FontSmall);
			}
			break;
		}

		CurrentItem = CurrentItem->Next;
	}
}
