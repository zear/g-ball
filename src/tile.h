#ifndef __TILE__
#define __TILE__

#include "SDL.h"

typedef struct {
	SDL_Surface *tileset;
	char *file;
	void *next;
} Tileset;

extern Tileset *tile;

typedef struct {
	Tileset *tileset;
	uint8_t x,y;
} Tile;

Tile allocTile(char *ent);

#endif //__TILE__
