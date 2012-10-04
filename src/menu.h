#ifndef _MENU_H_
#define _MENU_H_

typedef enum MenuActionEnum
{
	ACTION_NEW_GAME,
	ACTION_OPTIONS,
	ACTION_QUIT
} MenuAction;

typedef struct MenuItemStruct
{
	int number;
	MenuAction Action;
	char caption[21];
	struct MenuItemStruct *Next;
} MenuItem;

typedef struct MenuContainerStruct
{
	MenuItem *Menu;
	int size;
} MenuContainer;

MenuContainer *menuCreateNew(MenuContainer *Container, int number, char *caption, MenuAction Action);
void menuAction(MenuItem *Item);
void menuDeleteSingle(MenuContainer *Container);
void menuDeleteAll();
void menuLoadAll();
void menuDraw(MenuContainer *Container, int number, int x, int y);

extern MenuContainer *CurrentMenu;
extern MenuItem *SelectedItem;

extern MenuContainer *MenuMain;
extern MenuContainer *MenuOptions;

#endif /* _MENU_H_ */
