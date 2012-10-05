#ifndef _LOGO_H_
#define _LOGO_H_

#include <SDL.h>
#include "../global.h"

typedef struct LogoTileStruct
{
	Point Pos;
	int v;
	int bump;
} Tile;

struct LogoStruct
{
	SDL_Surface *bitmap;
	SDL_Rect clip[6];
	Tile tile[6];
	int done;
} Logo;

void logoLogic();

#endif /* _LOGO_H_ */
