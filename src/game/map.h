#ifndef _MAP_H_
#define _MAP_H_

#include <SDL.h>

#define TILE_SIZE	16

typedef struct MapStruct
{
	char *title;
	int w;
	int h;
	int **array;
	SDL_Surface *bitmap;
	SDL_Rect clip[256];
} Map;

extern Map CurMap;

#endif /* _MAP_H_ */
