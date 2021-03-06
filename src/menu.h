#ifndef _MENU_H_
#define _MENU_H_

typedef enum MenuActionEnum
{
	ACTION_NONE,
	ACTION_NEW_GAME,
	ACTION_OPTIONS,
	ACTION_QUIT,
	ACTION_OPTIONS_VIDEO,
	ACTION_OPTIONS_AUDIO,
	ACTION_OPTIONS_BACK
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
MenuItem *menuSwitchItem(MenuContainer *Container, int number);
void menuAction(MenuItem *Item);
void menuDeleteSingle(MenuContainer *Container);
void menuDeleteAll();
void menuLoadAll();
void menuInput();
void menuDrawSingle(MenuContainer *Container, int number, int x, int y);
void menuDraw(MenuContainer *Container, int x, int y);

extern MenuContainer *CurrentMenu;
extern MenuItem *SelectedItem;

extern MenuContainer *MenuMain;
extern MenuContainer *MenuOptions;

#endif /* _MENU_H_ */
