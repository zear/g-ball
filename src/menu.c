#include "menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "font.h"

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

void menuAction(MenuItem *Item)
{
	switch(Item->Action)
	{
		case ACTION_NEW_GAME:
			break;
		case ACTION_OPTIONS:
			break;
		case ACTION_QUIT:
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
			break;
		}

		CurrentItem = CurrentItem->Next;
	}
}
