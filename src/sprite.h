#ifndef __TILE__
#define __TILE__

#include "SDL.h"

typedef struct {
	SDL_Surface *surface;
	char w, h;
	char *file;
	void *next;
} SpriteSheet;

extern Tileset *tile;

typedef struct {
	SpriteSheet *spritesheet;
	uint8_t x,y;
} Sprite;

SpriteSheet spriteSheet_super(char *ent);

#endif //__TILE__
