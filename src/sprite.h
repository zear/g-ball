#ifndef __TILE__
#define __TILE__

#include "SDL.h"

typedef struct {
	SDL_Surface *tileset;
	char w, h;
	char *file;
	void *next;
} SpriteSheet;

extern Tileset *tile;

typedef struct {
	Tileset *tileset;
	uint8_t x,y;
} Sprite;

SpriteSheet spriteSheet_super(char *ent);

#endif //__TILE__
